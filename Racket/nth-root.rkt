#lang racket
;; kod z wykładu

(define identity
  (lambda (x) x))

(define (square x)
  (* x x))

(define (inc x) (+ 1 x))

(define (decr x) (- x 1))

(define (dist x y)
  (abs (- x y)))

(define (power x n)
  (if(<= n 1)
     x
     (* x (power x (decr n)))))

;;zad 2
(define (compose f g)
  (lambda (x) (f (g x))))

;;zad3
(define (repeated f n)
  (if (<= n 1)
      (identity f)
      (compose f (repeated f (- n 1)))))



(define (close-enough? x y)
  (< (dist x y) 0.00001))


(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (close-enough? x0 x1)
        x0
        (fix-point f x1))))

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

(define (sqrt-ad x)
  (fix-point (average-damp (lambda (y) (/ x y))) 1.0))


(define (nth-root-test x n k)
  (fix-point ((repeated average-damp k) (lambda (y) (/ x (power y (decr n))))) 1.0))

;; (nth-root-test 2 4 1)
(nth-root-test 2 4 2)

;;(nth-root-test 2 8 2)
(nth-root-test 2 8 3)
(nth-root-test 10 8 3)

(nth-root-test 10 16 4)

(nth-root-test 2521 32 5)
(nth-root-test 2515 11 4)
(nth-root-test 521521 11 3)
(nth-root-test 251 7 2)
;;liczba tlumien odpowiada logarytmowi dwojkowemu ze stopnia pierwiastka

(define (nth-root x n)
  (fix-point ((repeated average-damp (log n 2)) (lambda (y) (/ x (power y (decr n))))) 1.0))

(nth-root -0.125 3)
(nth-root 225 3)
(nth-root -1315 17)
(nth-root 0 16)
