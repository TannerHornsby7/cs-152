#lang typed/racket

;; CMSC15100 Winter 2022
;; Homework 4
;; Tanner Hornsby

;; include CS151-specific definitions
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;;Scale-By List Function
(: scale-by : Real (Listof Real) -> (Listof Real))
;;scales a list of real numbers by a real number
(define (scale-by a b)
  (match b
    [(cons x xr) (cons (* x a) (scale-by a xr))]
    ['() empty]))

;;TESTS
;;test list one (checking standard integer list)
(define inTestScaleList1 '(1 2 3))
(define outTestScaleList1 '(3 6 9))
;;test list two (checking empty lists)
(define inTestScaleList2 '())
(define outTestScaleList2 '())
;;check expect statements
(check-expect (scale-by 3 inTestScaleList1) outTestScaleList1)
(check-expect (scale-by 3 inTestScaleList2) outTestScaleList2)

;;Non-Zero List Function
(: non-zeros : (Listof Integer) -> (Listof Integer))
;;takes a list of integers and returns the list without elements of value 0.
(define (non-zeros l)
  (match l
    [(cons x xr) (if (= x 0)
                     (non-zeros xr)
                     (cons x (non-zeros xr)))]
    [_ empty]))

;;test list one (checking standard integer list)
(define inZerosList1 '(0 1 2 3))
(define outZerosList1 '(1 2 3))
;;test list two
(define inZerosList2 '(0 0 0 0))
(define outZerosList2 '())
;;test list three (checking empty lists)
(define inZerosList3 '())
(define outZerosList3 '())
;;check expect statements
;;(display (non-zeros inZerosList1))
(check-expect (non-zeros inZerosList1) outZerosList1)
(check-expect (non-zeros inZerosList2) outZerosList2)
(check-expect (non-zeros inZerosList3) outZerosList3)

;;Not Equal To Function
(: not-equal-to : Integer (Listof Integer) -> (Listof Integer))
;;Takes an integer and a list of integers and returns a list of integers without elements of the specified value.
(define (not-equal-to a L)
  (match L
      [(cons x xr) (if (not (= x a))
                       (cons x (not-equal-to a xr))
                       (not-equal-to a xr))]
      [_ empty]))

;;test list one (checking standard integer list)
(define inNEqualList1 '(0 1 2 3))
(define outNEqualList1 '(1 2 3))
;;test list two (checking empty lists)
(define inNEqualList2 '(4 4 5 3 4))
(define outNEqualList2 '(5 3))
;;test list three
(define inNEqualList3 '())
(define outNEqualList3 '())
;;check expect statements
;;(display (non-NEqual inNEqualList1))
(check-expect (not-equal-to 0 inNEqualList1) outNEqualList1)
(check-expect (not-equal-to 4 inNEqualList2) outNEqualList2)
(check-expect (not-equal-to 7 inNEqualList3) outNEqualList3)

;;List Product Function
(: list-product : (Listof Real) -> Real)
;;Computes the product of all the numbers in the list (return 1 for the empty list).
(define (list-product L)
  (match L
    [(cons x xr) (* x (list-product xr))]
    ['() 1]))

;;test list one (checking list of single integer value)
(define inLProdList1 '(1 1 1 1))
(define outLProdList1 '(1))
;;test list two (checking list of multiple different integers)
(define inLProdList2 '(3 4 10))
(define outLProdList2 '(5 3))
;;test list three (checking empty list)
(define inLProdList3 '())

;;check expect statements
;;(display (non-LProd inLProdList1))
(check-expect (list-product inLProdList1) 1)
(check-expect (list-product inLProdList2) 120)
(check-expect (list-product inLProdList3) 1)

;;List Xor Function
(: list-xor : (Listof Boolean) -> Boolean)
;;return true if exactly one item in the list is true and false otherwise.
;;Your solution should terminate if it sees more than one true item.
(define (list-xor L)
  (local
    {(: aux-true-counter : (Listof Boolean) -> Natural)
    (define (aux-true-counter L)
      (match L
        [(cons x xr) (+ (if x 1 0) (aux-true-counter xr)) ]
        [_ 0]))}

    (if (= (aux-true-counter L) 1) #t #f)))

;;test list one (checking heterogenous list with one true value)
(define inXorList1 '(#f #f #f #t))
;;test list two (checking heterogenous list with multiple true values)
(define inXorList2 '(#t #t #f))
;;test list three (checking empty list)
(define inXorList3 '())

;;check expect statements
;;(display (non-Xor inXorList1))
(check-expect (list-xor inXorList1) #t)
(check-expect (list-xor inXorList2) #f)
(check-expect (list-xor inXorList3) #f)

;;Add Lists Function
(: add-lists : (Listof Integer) (Listof Integer) -> (Listof Integer))
;;return a list that is the element-wise sum of the two lists.
;;If one list is longer than the other, ignore the excess elements; for example
(define (add-lists L1 L2)
  (match* (L1 L2)
        [((cons x1 xr1) (cons x2 xr2))  (cons (+ x1 x2) (add-lists xr1 xr2)) ]
        [(_ _) empty]))

;;test list one (checking two standard lists)
(define inAddList1a '(1 2 3))
(define inAddList1b '(1 2 3))
(define outAddList1 '(2 4 6))
;;test list two (checking two lists of different lengths)
(define inAddList2a '(6 9 0))
(define inAddList2b '(3 4))
(define outAddList2 '(9 13))
;;test list three (checking empty lists)
(define inAddList3a '())
(define inAddList3b '())
(define outAddList3 '())

;;check expect statements
(check-expect (add-lists inAddList1a inAddList1b) outAddList1)
(check-expect (add-lists inAddList2a inAddList2b) outAddList2)
(check-expect (add-lists inAddList3a inAddList3b) outAddList3)

;;That Many Function
(: that-many : (Listof Integer) -> (Listof (Listof Integer)))
;;builds a list of lists containing "that many" of each; for example,
(define (that-many L)
  (match L
        [(cons x xr)  (if (> x 0)
                          (cons (make-list x x) (that-many xr))
                          (cons empty (that-many xr)))]
        [_ empty]))

;;test list one (checking standard list)
(define inTManyList1 '(1 2 3))
(define outTManyList1 '((1) (2 2) (3 3 3)))
;;test list two (checking two lists of different lengths)
(define inTManyList2 '(4 1 -1 0))
(define outTManyList2 '((4 4 4 4) (1) () ()))
;;test list three (checking empty lists)
(define inTManyList3 '())
(define outTManyList3 '())

;;check expect statements
(check-expect (that-many inTManyList1) outTManyList1)
(check-expect (that-many inTManyList2) outTManyList2)
(check-expect (that-many inTManyList3) outTManyList3)

;;Insert Function
(: insert : Integer (Listof Integer)-> (Listof Integer))
;;given an integer n and a list of integers ns that are ordered by increasing value,
;;insert n into ns such that the order property is preserved.
(define (insert N ns)
  (match ns
        [(cons x xr)  (if (< N x)
                          (cons N (cons x xr))
                          (cons x (insert N xr)))]
        [_ empty]))

;;test list one (checking standard list)
(define inInsertList1 '(-2 1 3 17))
(define outInsertList1 '(-2 1 3 8 17))
;;test list two (checking two lists of different lengths)
(define inInsertList2 '(-2 1 3 17))
(define outInsertList2 '(-3 -2 1 3 17))
;;test list three (checking empty lists)
(define inInsertList3 '())
(define outInsertList3 '())

;;check expect statements
(check-expect (insert 8 inInsertList1) outInsertList1)
(check-expect (insert -3 inInsertList2) outInsertList2)
(check-expect (insert 0 inInsertList3) outInsertList3)

;;Ioata Function
(: iota : Natural -> (Listof Natural))
;;takes in a natural and returns a list of n+1 naturals
;; going to locally define an accumulator prod=0 and decrement prod by 1 for each recursive call until we reach the final call
(define (iota n)
  (local
    {(: aux-iota : Natural Natural (Listof Natural) -> (Listof Natural))
    (define (aux-iota n i prod)
      (if (<= n i) prod (cons i (aux-iota n (+ i 1) (list (+ i 1))))))}
    (aux-iota n 0 '(0))))
      

;;test list one (checking standard list)
(define outIotaList1 '(0 1 2 3))
;;test list two (checking two lists of different lengths)
(define outIotaList2 '(0 1 2 3 4 5 6))
;;test list three (checking empty lists)
(define outIotaList3 '(0 1))

;;check expect statements
(check-expect (iota 3) outIotaList1)
(check-expect (iota 6) outIotaList2)
(check-expect (iota 1) outIotaList3)

;;Prefix Sum Function
(: prefix-sum : (Listof Real) -> (Listof Real))
;;given a list of real numbers
;;return list of partial sums
;;(define (prefix-sum L)
 ;; (match L
  ;;  [(cons x xr) (if (< 0 (length xr))
   ;;                  (cons (+ x (list-ref xr 0)) (prefix-sum xr))
    ;;                 empty)]
   ;; [_ '()]))

(define (prefix-sum L)
  (local
    {(: aux-prefix : Real (Listof Real) -> (Listof Real))
     (define (aux-prefix acc n)
      (match n
        [(cons x xr) (cons (+ acc x) (aux-prefix (+ acc x) xr))]
        [_ empty]))}
    (aux-prefix 0 L)))

      

;;test list one (checking standard list)
(define inPList1 '(0 1 2 3))
(define outPList1 '(0 1 3 6))
;;test list two (checking two lists of different lengths)
(define inPList2 '(0))
(define outPList2 '(0))
;;test list three (checking empty lists)
(define inPList3 '())
(define outPList3 '())
;;check expect statements
(check-expect (prefix-sum inPList1) outPList1)
(check-expect (prefix-sum inPList2) outPList2)
(check-expect (prefix-sum inPList3) outPList3)

;; run tests
(test)