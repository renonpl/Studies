#lang racket
;;Wspolpraca z Artur Derechowski

(require "calc.rkt")

(define (def-name p)
  (car p))

(define (def-prods p)
  (cdr p))

(define (rule-name r)
  (car r))

(define (rule-body r)
  (cdr r))

(define (lookup-def g nt)
  (cond [(null? g) (error "unknown non-terminal" g)]
        [(eq? (def-name (car g)) nt) (def-prods (car g))]
        [else (lookup-def (cdr g) nt)]))

(define parse-error 'PARSEERROR)

(define (parse-error? r) (eq? r 'PARSEERROR))

(define (res v r)
  (cons v r))

(define (res-val r)
  (car r))

(define (res-input r)
  (cdr r))

;;

(define (token? e)
  (and (list? e)
       (> (length e) 0)
       (eq? (car e) 'token)))

(define (token-args e)
  (cdr e))

(define (nt? e)
  (symbol? e))

;;

(define (parse g e i)
  (cond [(token? e) (match-token (token-args e) i)]
        [(nt? e) (parse-nt g (lookup-def g e) i)]))

(define (parse-nt g ps i)
  (if (null? ps)
      parse-error
      (let ([r (parse-many g (rule-body (car ps)) i)])
        (if (parse-error? r)
            (parse-nt g (cdr ps) i)
            (res (cons (rule-name (car ps)) (res-val r))
                 (res-input r))))))

(define (parse-many g es i)
  (if (null? es)
      (res null i)
      (let ([r (parse g (car es) i)])
        (if (parse-error? r)
            parse-error
            (let ([rs (parse-many g (cdr es) (res-input r))])
              (if (parse-error? rs)
                  parse-error
                  (res (cons (res-val r) (res-val rs))
                       (res-input rs))))))))

(define (match-token xs i)
  (if (and (not (null? i))
           (member (car i) xs))
      (res (car i) (cdr i))
      parse-error))

;;

(define num-grammar
  '([digit {DIG (token #\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9)}]
    [numb {MANY digit numb}
          {SINGLE digit}]))

(define (node-name t)
  (car t))

(define (c->int c)
  (- (char->integer c) (char->integer #\0)))

(define (walk-tree-acc t acc)
  (cond [(eq? (node-name t) 'MANY)
         (walk-tree-acc
          (third t)
          (+ (* 10 acc) (c->int (second (second t)))))]
        [(eq? (node-name t) 'SINGLE)
         (+ (* 10 acc) (c->int (second (second t))))]))

(define (walk-tree t)
  (walk-tree-acc t 0))

;;

;;aktualizacja gramatyki z dodanym / i -
(define arith-grammar
  (append num-grammar
     '([add-expr {ADD-MANY   mult-expr (token #\+) add-expr}
                 {SUB-MANY mult-expr (token #\-) add-expr}
                 {ADD-SINGLE mult-expr}]
       [mult-expr {MULT-MANY base-expr (token #\*) mult-expr}
                  {DIV-MANY base-expr {token #\/} mult-expr}
                  {MULT-SINGLE base-expr}]
       [base-expr {BASE-NUM numb}
                  {PARENS (token #\() add-expr (token #\))}])))


(define (arith-walk-tree t)
  (cond [(eq? (node-name t) 'ADD-SINGLE)
         (arith-walk-tree (second t))]
        [(eq? (node-name t) 'MULT-SINGLE)
         (arith-walk-tree (second t))]
        [(eq? (node-name t) 'SUB-SINGLE)
         (arith-walk-tree (second t))]                           
        [(eq? (node-name t) 'ADD-MANY)
         (binop-cons
          '+
          (arith-walk-tree (second t))
          (arith-walk-tree (fourth t))
          )]
        [(eq? (node-name t) 'MULT-MANY)
         (binop-cons
          '*
          (arith-walk-tree (second t))
          (arith-walk-tree (fourth t))
          )]
        [(eq? (node-name t) 'SUB-MANY)
         (binop-cons
          '-
          (arith-walk-tree (second t))
          (arith-walk-tree (fourth t))
          )       
         ]
        [(eq? (node-name t) 'DIV-MANY)
         (binop-cons
          '/
          (arith-walk-tree (second t))
          (arith-walk-tree (fourth t))
          )       
         ]
        [(eq? (node-name t) 'BASE-NUM)
         (walk-tree (second t))]
        [(eq? (node-name t) 'PARENS)
         (arith-walk-tree (third t))]))


;;funkcja fix-binop naprawia drzewo, aby - i / dzialal tak jak chcielismy
;;wedlug tego przeksztalcenia / ma troche wiekszy priorytet od *, a - od + jednak nie wplywa to na wynik obliczen

(define (fix-binop e)
  (cond [(number? e) e]
        [ (or (eq? (binop-op e) '+) (eq? (binop-op e) '*)) (binop-cons (binop-op e) (binop-left e) (fix-binop (binop-right e)))] ;;dzielenia i mnozenia nie przeksztalcamy
        [else
         (if (number? (binop-right e)) e ;;sprawdzamy jaka jest prawa strona
             (if (and (or (eq? '* (binop-op (binop-right e))) (eq? '/ (binop-op (binop-right e)))) (eq? '- (binop-op e))) ;;jesli cos po prawej ma wyszy priorytet to nie przeksztalcamy
                      (binop-cons (binop-op e) (binop-left e) (fix-binop (binop-cons (binop-op (binop-right e)) (binop-left (binop-right e)) (binop-right (binop-right e))))) ;; tylko naprawiamy prawa strone
          (fix-binop (binop-cons (binop-op (binop-right e)) ;;a jesli nie, to w lewym binope umieszczamy dany operator, lewe poddrzewo i lewe podrzewo prawego binopa
                      (binop-cons (binop-op e) (binop-left e) (binop-left (binop-right e))) ;;a to wszystko laczymy operatorem z prawego poddrzewa z dalsza czescia i to wszystko naprawiamy
                      (binop-right (binop-right e))))))]))

;;do calca dorzucamy fixa
(define (calc s)
 (eval
  (fix-binop
  (arith-walk-tree
   (car
    (parse
       arith-grammar
       'add-expr
       (string->list s)))))))

;;TESTY
(calc "27*3")
(calc "26-3")
(calc "26-3")
(parse arith-grammar 'add-expr (string->list "2-5"))
(parse arith-grammar 'add-expr (string->list "2-5"))
(parse arith-grammar 'add-expr (string->list "2-5+3"))
(parse arith-grammar 'add-expr (string->list "2-3+5*383"))
(parse arith-grammar 'add-expr (string->list "3-6-8-15"))
(arith-walk-tree (car (parse arith-grammar 'add-expr (string->list "3-6-8-15-17"))))
(fix-binop (arith-walk-tree (car (parse arith-grammar 'add-expr (string->list "3-6*8-15*41+17")))))
(calc "3-6-8-15")
(calc "3-6-8-15*41+17")
(calc "1/6/8/72*18")
(fix-binop (arith-walk-tree (car (parse arith-grammar 'add-expr (string->list "3-3*5*7/3")))))
(calc "3-3*5*7/3")
(calc "61-1/67*42*67/15")
(calc "3-3*5*7/3")
(calc "7-5-7-2-6/6")