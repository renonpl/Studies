#lang racket

(define identity
  (lambda (x) x))

(define (square x)
  (* x x))

(define (inc x) (+ 1 x))

(define (decr x) (- x 1))

(define (dist x y)
  (abs (- x y)))


(define (cont-iter num den k)
  (define (cont i value)
    (if (= i 0)
        value
        (cont (decr i) (/ (num i) (+ (den i) value)))))
  (cont k 0))


(define (priori num den)
    (define (pr-it iter a-value alast-value b-value blast-value)
      (let ((approx 0.0001))
       (if (and (not (= blast-value 0)) (not (= a-value 0)) (< (dist (/ a-value b-value) (/ alast-value blast-value)) approx))
            (/ alast-value blast-value)
            (pr-it (inc iter)
                   (+ (* (den iter) a-value) (* (num iter) alast-value))
                    a-value
                    (+ (* (den iter) b-value) (* (num iter) blast-value))
                    b-value))))
  (pr-it 1 0 1 1 0))


(priori (lambda (x) 1.0) (lambda (x) 1.0))
(cont-iter (lambda (x) 1.0) (lambda (x) 1.0) 100)

(priori (lambda (x) 5.0) (lambda (x) 5.0))
(cont-iter (lambda (x) 5.0) (lambda (x) 5.0) 100)

(priori (lambda (x) (square x)) (lambda (x) (* 3.0 x)))
(cont-iter (lambda (x) (square x)) (lambda (x) (* 3.0 x)) 100)

(priori (lambda (x) (atan x)) (lambda (x) 1.0))
(cont-iter (lambda (x) (atan x)) (lambda (x) 1.0) 100)

