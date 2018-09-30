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

;;
;; WHILE
;;

; memory

(define empty-mem
  null)

(define (set-mem x v m)
  (cond [(null? m)
         (list (cons x v))]
        [(eq? x (caar m))
         (cons (cons x v) (cdr m))]
        [else
         (cons (car m) (set-mem x v (cdr m)))]))

(define (get-mem x m)
  (cond [(null? m) 0]
        [(eq? x (caar m)) (cdar m)]
        [else (get-mem x (cdr m))]))

; arith and bool expressions: syntax and semantics

(define (const? t)
  (number? t))

(define (true? t)
  (eq? t 'true))

(define (false? t)
  (eq? t 'false))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= not and or mod power-mod))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]
        [(eq? op 'not) not]
        [(eq? op 'and) (lambda x (andmap identity x))]
        [(eq? op 'or) (lambda x (ormap identity x))]
        [(eq? op 'mod) modulo]
        [(eq? op 'power-mod) (lambda (x y z) (power-mod x y z))]))
        ;;[(eq? op 'rand) (lambda (max) (min max 4))])) ; chosen by fair dice roll.
                                                      ; guaranteed to be random.

(define (var? t)
  (symbol? t))

(define (eval-arith e m)  ;;wszedzie eval-arith zwraca pare
  (cond [(true? e) (res true (get-mem 'seed m))]
        [(false? e) (res false (get-mem 'seed m))]
        [(var? e) (res (get-mem e m) (get-mem 'seed m))]
        [(rand? e) ((rand (res-val (eval-arith (cadr e) m))) (get-mem 'seed m))]
        [(op? e)
         (res (apply
          (op->proc (op-op e))
          (map (lambda (x) (res-val (eval-arith x m))) ;;po operatorze nie moze byc funkcji rand, bo nie wydobedziemy z niej ziarna
               (op-args e))) (get-mem 'seed m))]
        [(const? e) (res e (get-mem 'seed m))]))

;; syntax of commands

(define (assign? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (second t) ':=)))

(define (assign-var e)
  (first e))

(define (assign-expr e)
  (third e))

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

(define (while? t)
  (tagged-tuple? 'while 3 t))

(define (while-cond t)
  (second t))

(define (while-expr t)
  (third t))

(define (block? t)
  (list? t))

;; state

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;; psedo-random generator

(define initial-seed
  123456789)

(define (rand max)
  (lambda (i)
    (let ([v (modulo (+ (* 1103515245 i) 12345) (expt 2 32))])
      (res (modulo v max) v))))

(define (rand? e)
  (and (list? e)
       (= 2 (length e))
       (eq? 'rand (car e))))

;; WHILE interpreter

(define (old-eval e m)
  (cond [(assign? e)
         (let ((new-val (eval-arith (assign-expr e) m))) ;;zmienony eval zwraca pare - wartosc zmiennej i aktualne ziarno
         (set-mem
          (assign-var e)
          (res-val new-val)
          (set-mem
           'seed
           (res-state new-val) m)))] ;;wstawiamy ziarno do pamieci, a potem zmienna
        [(if? e)
         (if (res-val (eval-arith (if-cond e) m)) ;;sprawdzamy czy wartosc zachodzi
             (old-eval (if-then e) m)
             (old-eval (if-else e) m))]
        [(while? e)
         (if (res-val (eval-arith (while-cond e) m))
             (old-eval e (old-eval (while-expr e) m))
             m)]
        [(block? e)
         (if (null? e)
             m
             (old-eval (cdr e) (old-eval (car e) m)))]))

(define (eval e m seed)
  (old-eval e (set-mem 'seed  seed m))) ;;do starego evala dorzucam pamiec z ziarnem

(define (run e)
  (eval e  empty-mem initial-seed))

;;Fermat
;;dodalem do operatorow funkcje power-mod
;;bierze ona 3 argumenty i wylicza algorytmem szybkiego potegowania n'ta potege bazy zmodulowana przez mod
(define (power-mod base n mod)
  (if (= n 0)
      1
      (if (= (modulo n 2) 1)
          (modulo (* base (power-mod base (- n 1) mod)) mod)
          (let ((temp (power-mod base (/ n 2) mod)))
            (modulo (* temp temp) mod)))))


(define fermat-test
  '{
    (composite := false)
    (while (> k 0)
           ( (a := (rand (- n 4)))
             (a := (+ a 2))
             (a := (power-mod a (- n 1) n))                   
             (if (= a 1)
                 (k := (- k 1))
                 ( (k := 0)
                   (composite := true)))
                    ))}
  )

(define (probably-prime? n k) ; check if a number n is prime using
                              ; k iterations of Fermat's primality
                              ; test
  (let ([memory (set-mem 'k k
                (set-mem 'n n empty-mem))])
    (not (get-mem
           'composite
           (eval fermat-test memory initial-seed)))))


;;TESTY
;;oryginalny generator bierze minimum z 4 i podanego maxa
(run '( (z := (rand 512))
        (x := (rand 1254))
        (y := (rand 231))
        (p := (rand 14))))

(probably-prime? 5 2)
(probably-prime? 1024 5)
(probably-prime? 21 3)
(probably-prime? 4112472930633 30)
(probably-prime? (* 11 13 17 19) 20)
(probably-prime? 1729 20) ;;liczby Carmichaela
(probably-prime? 561 5)
(probably-prime? 340561 5) ;;dla malej ilosci iteracji przechodzi
(probably-prime? 42710135253 5) ;;zwykla liczba
(probably-prime? (- (expt 2 31) 1) 20) ;;liczby pierwsza
(probably-prime? 12049 20)
(probably-prime? 16381 20) 