#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))


(define (hole-context e)
  (define (helper e accu)
    (cond
        [(hole? e) accu] ;; jak dojddziemy do hole to zwracamy accu
        [(binop? e) (if (arith/let/hole-expr? (binop-left e)) ;;sprawdzamy gdzie jest hole
                     (helper (binop-left e) accu)
                     (helper (binop-right e) accu))]
        [(let? e) (if (arith/let/hole-expr? (let-expr e)) ;;jesli hole jest w expr
                      (helper (let-expr e) (cons (let-def-var (let-def e)) accu)) ;; to bierzemy zmienna z def
                      accu)])) ;; jak jest w def to zwracamy accu
   (remove-duplicates (helper e null)))


;;pare testow zapisanych w liscie par(dane,wynik)
(define (test)
  (define tests '(((+ 3 hole) ())
                  ((let (x 3) (let (y 7) (+ x hole))) (y x))
                  ((let (x 3) (let (y hole) (+ x 3))) (x))
                  ((let (x hole) (let (y 7) (+ x 3))) ())
                  ((let (piesek 1) (let (kotek 2) (let (chomik 5) (let (piesek 9) hole)))) (piesek chomik kotek))
                  ((+ (let (x 4) 5) hole) ())
                  ((+ (let (y 7) (let (w 4) (+ 4 hole))) 6) (w y))
                  ((+ (let (w 6) (+ 3 7)) (let (ala 62) (let (beta 13) (+ (- 42 ala) (* beta (let (haha 141) (- 4 hole))))))) (beta ala haha))))
  (define (checker ls)
    (if(null? ls) #t
       (let* ((p (car ls))
             (context (hole-context (car p))))
         (if (and (andmap (lambda (x) ;;sprawdzam czy kazdy z wyniku hole-context jest 
                       (member x (cadr p))) context) ;; w naszym sprawdzonym wyniku
                  (= (length context) (length (cadr p)))) ;; i czy dlugosci sa te same(czyli, ze nie ma duplikatow)
             (checker (cdr ls))
               #f))))
 (checker tests))
