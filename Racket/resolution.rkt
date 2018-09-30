#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości
(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;; reprezentacja danych wejściowych (z ćwiczeń)
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

;; przydatne predykaty na zmiennych
(define (var<? x y)
  (symbol<? x y))

(define (var=? x y)
  (eq? x y))

(define (literal? x)
  (and (tagged-tuple? 'literal 3 x)
       (boolean? (cadr x))
       (var? (caddr x))))

(define (literal pol x)
  (list 'literal pol x))

(define (literal-pol x)
  (cadr x))

(define (literal-var x)
  (caddr x))

(define (clause? x)
  (and (tagged-list? 'clause x)
       (andmap literal? (cdr x))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? x)
  (and (tagged-list? 'cnf x)
       (andmap clause? (cdr x))))

(define (cnf . cs)
    (cons 'cnf cs))

(define (cnf-clauses x)
  (cdr x))

;; oblicza wartość formuły w CNF z częściowym wartościowaniem. jeśli zmienna nie jest
;; zwartościowana, literał jest uznawany za fałszywy.
(define (valuate-partial val form)
  (define (val-lit l)
    (let ((r (assoc (literal-var l) val)))
      (cond
       [(not r)  false]
       [(cadr r) (literal-pol l)]
       [else     (not (literal-pol l))])))
  (define (val-clause c)
    (ormap val-lit (clause-lits c)))
  (andmap val-clause (cnf-clauses form)))

;; reprezentacja dowodów sprzeczności

(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (proof-axiom c)
  (list 'axiom c))

(define (axiom-clause p)
  (cadr p))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (proof-res x pp pn)
  (list 'resolve x pp pn))

(define (res-var p)
  (cadr p))

(define (res-proof-pos p)
  (caddr p))

(define (res-proof-neg p)
  (cadddr p))

;; sprawdza strukturę, ale nie poprawność dowodu
(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;; procedura sprawdzająca poprawność dowodu
(define (check-proof pf form)
  (define (run-axiom c)
    (displayln (list 'checking 'axiom c))
    (and (member c (cnf-clauses form))
         (clause-lits c)))
  (define (run-res x cpos cneg)
    (displayln (list 'checking 'resolution 'of x 'for cpos 'and cneg))
    (and (findf (lambda (l) (and (literal-pol l)
                                 (eq? x (literal-var l))))
                cpos)
         (findf (lambda (l) (and (not (literal-pol l))
                                 (eq? x (literal-var l))))
                cneg)
         (append (remove* (list (literal true x))  cpos)
                 (remove* (list (literal false x)) cneg))))
  (define (run-proof pf)
    (cond
     [(axiom? pf) (run-axiom (axiom-clause pf))]
     [(res? pf)   (run-res (res-var pf)
                           (run-proof (res-proof-pos pf))
                           (run-proof (res-proof-neg pf)))]
     [else        false]))
  (null? (run-proof pf)))


;; reprezentacja wewnętrzna

;; sprawdza posortowanie w porządku ściśle rosnącym, bez duplikatów
(define (sorted? vs)
  (or (null? vs)
      (null? (cdr vs))
      (and (var<? (car vs) (cadr vs))
           (sorted? (cdr vs)))))

(define (sorted-varlist? x)
  (and (list? x)
       (andmap var? x)
       (sorted? x)))

;; klauzulę reprezentujemy jako parę list — osobno wystąpienia pozytywne i negatywne. Dodatkowo
;; pamiętamy wyprowadzenie tej klauzuli (dowód) i jej rozmiar.
(define (res-clause? x)
  (and (tagged-tuple? 'res-int 5 x)
       (sorted-varlist? (second x))
       (sorted-varlist? (third x))
       (= (fourth x) (+ (length (second x)) (length (third x))))
       (proof? (fifth x))))

(define (res-clause pos neg proof)
  (list 'res-int pos neg (+ (length pos) (length neg)) proof))

(define (res-clause-pos c)
  (second c))

(define (res-clause-neg c)
  (third c))

(define (res-clause-size c)
  (fourth c))

(define (res-clause-proof c)
  (fifth c))

;; przedstawia klauzulę jako parę list zmiennych występujących odpowiednio pozytywnie i negatywnie
(define (print-res-clause c)
  (list (res-clause-pos c) (res-clause-neg c)))

;; sprawdzanie klauzuli sprzecznej
(define (clause-false? c)
  (and (null? (res-clause-pos c))
       (null? (res-clause-neg c))))

;; pomocnicze procedury: scalanie i usuwanie duplikatów z list posortowanych
(define (merge-vars xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [(var<? (car xs) (car ys))
         (cons (car xs) (merge-vars (cdr xs) ys))]
        [(var<? (car ys) (car xs))
         (cons (car ys) (merge-vars xs (cdr ys)))]
        [else (cons (car xs) (merge-vars (cdr xs) (cdr ys)))]))

(define (remove-duplicates-vars xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [(var=? (car xs) (cadr xs)) (remove-duplicates-vars (cdr xs))]
        [else (cons (car xs) (remove-duplicates-vars (cdr xs)))]))

(define (rev-append xs ys)
  (if (null? xs) ys
      (rev-append (cdr xs) (cons (car xs) ys))))

;; TODO: miejsce na uzupełnienie własnych funkcji pomocniczych

;;procedura sprawdza czy jakis element z list-pos wystepuje w list-neg
(define (find-neg list-pos list-neg)
    (if (null? list-pos)
        #f
        (if (member (car list-pos) list-neg)
            (car list-pos)
            (find-neg (cdr list-pos) list-neg))))

;;z find-neg otrzymujemy albo falsz albo jakis element 
(define (clause-trivial? c)
  (var? (find-neg (res-clause-pos c) (res-clause-neg c))))
 

;;resolve szuka najpierw zmienna pozytywna w c1 i negatywna w c2, a jak nie to wywoluje switchera, ktory zamienia klauzule miejscami
(define (resolve c1 c2)
  (define (switcher c1 c2 l)
      (let ((x (find-neg (res-clause-pos c1) (res-clause-neg c2))))
      (if (eq? x #f)
          (if (= l 1)
              (switcher c2 c1 0)
              #f)
          (res-clause (remove x (merge-vars (res-clause-pos c1) (res-clause-pos c2))) ;;merge-vars usuwa duplikaty wiec wystarczy
                      (remove x (merge-vars (res-clause-neg c1) (res-clause-neg c2))) ;; usunac zmienna po ktorej przeprowadzamy rezolucje
                      (proof-res x (res-clause-proof c1) (res-clause-proof c2))))))
  (switcher c1 c2 1))



(define (resolve-single-prove s-clause checked pending)
  ;; TODO: zaimplementuj!
  ;; Poniższa implementacja działa w ten sam sposób co dla większych klauzul — łatwo ją poprawić!                            
  (let ((temp-checked (sort-clauses (map (lambda (x)            ;;kazdy elemeny z listy checked zamieniam na rezolwente albo zostawiam bez zmian
                                       (let ((temp-resolve (resolve s-clause x)))
                                         (if (false? temp-resolve)
                                             x
                                             temp-resolve)))
                                     checked)))
        (temp-pending (sort-clauses (map (lambda (x)  ;;analogicznie klauzule z penda
                                   (let ((temp-resolve (resolve s-clause x)))
                                     (if (false? temp-resolve)
                                         x
                                         temp-resolve)))
                                 pending))))
    
    (if (and  (pair? temp-checked) (=  (res-clause-size (car temp-checked)) 0)) ;;listy sa posortowane
        (list 'unsat (res-clause-proof (car temp-checked))) ;;wiec wystarczy sprawdzic czy ktorys z pierwszych elementow nie na nich nie jest 
        (if (and  (pair? temp-pending) (=  (res-clause-size (car temp-pending)) 0)) ;; pusty/falszywy
            (list 'unsat (res-clause-proof (car temp-pending)))
            (resolve-prove (cons s-clause temp-checked) temp-pending)))))

;; wstawianie klauzuli w posortowaną względem rozmiaru listę klauzul
(define (insert nc ncs)
  (cond
   [(null? ncs)                     (list nc)]
   [(< (res-clause-size nc)
       (res-clause-size (car ncs))) (cons nc ncs)]
   [else                            (cons (car ncs) (insert nc (cdr ncs)))]))

;; sortowanie klauzul względem rozmiaru (funkcja biblioteczna sort)
(define (sort-clauses cs)
  (sort cs < #:key res-clause-size))

;; główna procedura szukająca dowodu sprzeczności
;; zakładamy że w checked i pending nigdy nie ma klauzuli sprzecznej
(define (resolve-prove checked pending)
  (cond
   ;; jeśli lista pending jest pusta, to checked jest zamknięta na rezolucję czyli spełnialna
   [(null? pending) (generate-valuation (sort-clauses checked))]
   ;; jeśli klauzula ma jeden literał, to możemy traktować łatwo i efektywnie ją przetworzyć
   [(= 1 (res-clause-size (car pending)))
    (resolve-single-prove (car pending) checked (cdr pending))]
   ;; w przeciwnym wypadku wykonujemy rezolucję z wszystkimi klauzulami już sprawdzonymi, a
   ;; następnie dodajemy otrzymane klauzule do zbioru i kontynuujemy obliczenia
   [else
    (let* ((next-clause  (car pending))
           (rest-pending (cdr pending))
           (resolvents   (filter-map (lambda (c) (resolve c next-clause))
                                     checked))
           (sorted-rs    (sort-clauses resolvents)))
      (subsume-add-prove (cons next-clause checked) rest-pending sorted-rs))]))

;; procedura upraszczająca stan obliczeń biorąc pod uwagę świeżo wygenerowane klauzule i
;; kontynuująca obliczenia. Do uzupełnienia.
(define (subsume-add-prove checked pending new)
  (cond
   [(null? new)                 (resolve-prove checked pending)]
   ;; jeśli klauzula do przetworzenia jest sprzeczna to jej wyprowadzenie jest dowodem sprzeczności
   ;; początkowej formuły
   [(clause-false? (car new))   (list 'unsat (res-clause-proof (car new)))]
   ;; jeśli klauzula jest trywialna to nie ma potrzeby jej przetwarzać
   [(clause-trivial? (car new)) (subsume-add-prove checked pending (cdr new))]
   [else
    ;; TODO: zaimplementuj!
    ;; Poniższa implementacja nie sprawdza czy nowa klauzula nie jest lepsza (bądź gorsza) od już
    ;; rozpatrzonych; popraw to!
    (let ((cl (car new)))
      (if (or (ormap (lambda (x) (concluding x cl)) checked) ;;sprawdza czy new jest latwiejsza klauzula
              (ormap (lambda (x) (concluding x cl)) pending))
          (subsume-add-prove checked pending (cdr new)) ;; jak jest to pomija
          (subsume-add-prove (filter (lambda (x) (not (concluding x cl))) checked) (insert cl (filter (lambda (x) (not (concluding x cl))) pending)) (cdr new))))]))
;;jak nie to filtruje i wyrzuca wszystkie latwiejsze klauzuli


(define (concluding cl cx) ;;procedura sprawdzajaca czy klauzula cl zawiera sie w klauzuli cx
  (list? (and (andmap (lambda (x) (member x (res-clause-pos cl))) (res-clause-pos cx)) ;;jak tak to andmap zwraca liste a jak nie to false
       (andmap (lambda (x) (member x (res-clause-neg cl))) (res-clause-neg cx)))))


(define (generate-valuation resolved)
  ;; TODO: zaimplementuj!
  ;; Ta implementacja mówi tylko że formuła może być spełniona, ale nie mówi jak. Uzupełnij ją!
  (define (reduction list elem) ;;procedura, ktora usuwa z zadanej listy klauzule spelnione przez zadany element
    (define (iterator accu ls)
      (if (null? ls) accu
          (let ((cl (car ls)))
            (if (cadr elem)  ;;sprawdzamy jaka wartosc ma zmienna
                (if (member (car elem) (res-clause-pos cl)) ;; jesli element ma pozytywne wystapienie w danej klauzuli
                    (iterator accu (cdr ls))  ;; to go pozbywamy sie, jak nie, to usuwamy potencjalne wystapnienie w liscie zanegowanych zmiennych
                    (iterator (cons (res-clause (res-clause-pos cl) (remove (car elem) (res-clause-neg cl)) (res-clause-proof cl)) accu) (cdr ls)))
                (if (member (car elem) (res-clause-neg cl)) ;; analogicznie przy negatywnych wystapieniach
                    (iterator accu (cdr ls))
                    (iterator (cons (res-clause (remove (car elem)(res-clause-pos cl)) (res-clause-neg cl) (res-clause-proof cl)) accu) (cdr ls)))))))
    (iterator null list))
  
  (define (generator accu ls)
    (if (null? ls) accu
          (let ((cl (car ls)))
            (if (= (res-clause-size cl) 0)
                (generator accu (cdr ls)) ;;procedura reduction moze wygenerowac klauzule o zerowym rozmiarze, ktore nalezy pominac
                (if (null? (res-clause-pos cl)) ;;sprawdzamy czy sa tylko zmienne zanegowane
                    (let ((x (list (car (res-clause-neg cl)) #f))) ;;jak tak to pierwszej zmiennej przypisujemy falsz
                      (generator (cons x accu) (sort-clauses (reduction ls x)))) ;; i dodajemy ja do accu a liste redukujemy i sortujemy
                    (let ((x (list (car (res-clause-pos cl)) #t))) ;; analogicznie
                      (generator (cons x accu) (sort-clauses (reduction ls x)))))))))
 (list 'sat (generator null resolved)))

;; procedura przetwarzające wejściowy CNF na wewnętrzną reprezentację klauzul
(define (form->clauses f)
  (define (conv-clause c)
    (define (aux ls pos neg)
      (cond
       [(null? ls)
        (res-clause (remove-duplicates-vars (sort pos var<?))
                    (remove-duplicates-vars (sort neg var<?))
                    (proof-axiom c))]
       [(literal-pol (car ls))
        (aux (cdr ls)
             (cons (literal-var (car ls)) pos)
             neg)]
       [else
        (aux (cdr ls)
             pos
             (cons (literal-var (car ls)) neg))]))
    (aux (clause-lits c) null null))
  (map conv-clause (cnf-clauses f)))

(define (prove form)
  (let* ((clauses (form->clauses form)))
    (subsume-add-prove '() '() clauses)))

;; procedura testująca: próbuje dowieść sprzeczność formuły i sprawdza czy wygenerowany
;; dowód/waluacja są poprawne. Uwaga: żeby działała dla formuł spełnialnych trzeba umieć wygenerować
;; poprawną waluację.
(define (prove-and-check form)
  (let* ((res (prove form))
         (sat (car res))
         (pf-val (cadr res)))
    (if (eq? sat 'sat)
        (valuate-partial pf-val form)
        (check-proof pf-val form))))

;;; TODO: poniżej wpisz swoje testy


(define t1 (res-clause '(q w r) '(z) 'axiom))
(define t2 (res-clause '(r) '(z q w) 'axiom))
(define t3 (res-clause '(a) '(a b c d p r) 'axiom))
(define t4 (res-clause '(r p) '(z q w) 'axiom))
(define t5 (res-clause '(a p s) '(a b c d p r) 'axiom))
(clause-trivial? t3)
(clause-trivial? t2)
(resolve t1 t2)
(resolve t2 t1)
(resolve t3 t5)
(resolve t4 t2)

(define test (cnf (clause  (literal #t 'p) (literal #f 'q))
                        (clause (literal #f 'p) (literal #t 'q))))

(define test2 (cnf (clause  (literal #t 'p) (literal #t 'q))
                        (clause (literal #f 'p) (literal #f 'p))))

(define test3 (cnf (clause  (literal #t 'p) (literal #f 'q))
                   (clause (literal #t 'w) (literal #t 'q))
                   (clause  (literal #t 'p) (literal #f 'w))
                   (clause (literal #f 'p) (literal #f 'q) (literal #f 'w))))

(define test4 (cnf (clause  (literal #t 'p) (literal #t 'w))
                   (clause (literal #t 'q) (literal #t 'p))
                   (clause (literal #f 'q) (literal #f 'p))
                   (clause (literal #t 'p) (literal #f 'w))
                   (clause (literal #f 'w) (literal #t 'l))))

(define test5 (cnf (clause  (literal #t 'p) (literal #t 'q))
                    (clause (literal #t 'p) (literal #f 'q))
                    (clause (literal #f 'p) (literal #t 'q))
                    (clause (literal #f 'p) (literal #f 'q))))

(define test6 (cnf (clause  (literal #t 'q) (literal #t 'p))))

(define test7 (cnf (clause  (literal #t 'p))
                    (clause (literal #f 'p))))

(prove test)
(prove-and-check test)
(prove-and-check test2)
(prove test3)
(prove-and-check test3)
(prove test4)
(prove-and-check test4)
(prove test6)
(prove-and-check test6)
(prove-and-check test5)
(prove-and-check test7)
