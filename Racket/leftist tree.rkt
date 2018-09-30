#lang racket

(define (inc n)
  (+ n 1))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (list? h)
       (= 5 (length h))
       (eq? (car h) 'hnode)
       (natural? (caddr h))))

(define (make-node elem heap-a heap-b)
  (if (< (rank heap-a) (rank heap-b))
      (list 'hnode elem (inc (rank heap-a)) heap-b heap-a) ;; jak ranga heap-b jest wieksza, to heap-a jest prawym kopcem
      (list 'hnode elem (inc (rank heap-b)) heap-a heap-b))) ;; jak nie to heap-a zostaje prawym kopcem
      ;; ;;zwraca liste z kolejno symbolem, elementem, zwiekszona ragna prawego kopca, wskaznikami na lewy i prawy kopiec


(define (node-elem h)
  (second h))

(define (node-left h)
  (fourth h))

(define (node-right h)
  (fifth h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (node-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (node-left h))
           (heap? (node-right h))
           (<= (rank (node-right h))
               (rank (node-left h)))
           (= (rank h) (inc (rank (node-right h))))
           (hord? (elem-priority (node-elem h))
                  (node-left h))
           (hord? (elem-priority (node-elem h))
                  (node-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (third h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-node elt leaf leaf)))

(define (heap-min heap)
  (node-elem heap))

(define (heap-pop heap)
  (heap-merge (node-left heap) (node-right heap)))

(define (heap-merge h1 h2)
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [else (if (> (elem-priority (heap-min h1)) (elem-priority (heap-min h2)))  ;;jak priorytet elemntu na gorze h1 jest wiekszy
         (make-node (heap-min h2) (node-left h2) (heap-merge (node-right h2) h1)) ;; to bierzemy element z h2 i bierzemy wskazniki na lewe poddrzewo h2 i zmergowane prawe z h1
         (make-node (heap-min h1) (node-left h1) (heap-merge (node-right h1) h2)))])) ;; jak h2 ma wiekszy to odwrotnie


;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))


;;testy
(define x1 (randlist 1000 10))
(sorted? (heapsort x1))
(define x2 (randlist 10 5))
x2
(sorted? (heapsort x2))
(heapsort x2)
(define x3 (randlist 1000 1000))
(sorted? (heapsort x3))
(define x4 (randlist 100 1000))
(sorted? (heapsort x4))
(define x5 (randlist 3 10))
(sorted? (heapsort x5))
(define x6 (randlist 2 10))
(sorted? (heapsort x6))
(define x7 (randlist 10000 42))
(sorted? (heapsort x7))
(define x8 (randlist 3000 101))
(sorted? (heapsort x8))
(define x9 (randlist 3 2))
(heapsort x9)
