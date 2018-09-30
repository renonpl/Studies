#lang racket

(define (dist x y)
  (abs (- x y)))

(define (cube x)
    (* x x x))

(define (cube-root x)
  ; poprawianie przyblizenia pierwiastka
  (define (improve approx)
    (/ (+ (/ x (* approx approx)) (* 2 approx)) 3))
  ; sprawdzanie dokladnosci rozwiazania
  (define (good-enough? approx)
    (< (dist x (cube approx)) 0.001))
  ; główna procedura znajdująca rozwiązanie
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
 
  (iter 1.0))

;testy
(cube-root 8)
(cube-root 125)
(cube-root 1)
(cube-root 0)
(cube-root -8)
(cube-root 1000)
(cube-root 6.7)
(cube-root 1000000001)
(cube-root 2)
(cube-root -3)
(cube-root 3)
(cube-root -999)