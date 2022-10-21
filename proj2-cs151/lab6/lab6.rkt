#lang typed/racket

(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

(define-struct (Pair A B)
    ([fst : A]
     [snd : B]))

(define-type (Binary-Tree T) (U 'Empty (Node T)))

(define-struct (Node T)
    ([l-kid : (Binary-Tree T)]
     [item : T]
     [r-kid : (Binary-Tree T)]))

(define-type Order (U '< '= '>))

(define-type (Cmp T) (T T -> Order))

(define-struct (Set T)
    ([cmp : (Cmp T)]
     [bst : (Binary-Tree T)]))


;;in between tree test
(: between : (All (T) T T (Set T) -> (Listof T)))
;; Given, in order, a lower bound, an upper bound, and a Set, generate
;; a list of all the elements in the set that are strictly greater than the lower bound, and strictly less than the upper bound.
;; This list should be in ascending order. If no elements are within the range, produce an empty list.
;; Exploit the BST ordering property to avoid looking in parts of the tree that cannot contain
;; relevant entries, and to avoid performing a separate sorting operation.
(: tree->list : (All (T) (Binary-Tree T) -> (Listof T)))
(define (tree->list tr)
  (local
  {(: leaves : (All (T) (Binary-Tree T) (Listof T) -> (Listof T)))
 ;; accumulate node-values in right-to-left in-order traversal
   (define (leaves tr acc)
     (match tr
       [(Node l v r) (leaves l (cons v (leaves r acc)))]
       [’Empty acc]))}
  (leaves tr '())))

(define (between l u s)
 (match s
   ['Empty '()]
   [(Set cmp tr)
    (match* ((cmp value l)(cmp value u))
           [('< '>) #t]
           [(_ _) #f])
      (filter within-bounds?
          (tree->list tr)))]))


;;creating test inputs and outputs
;; comparisons on integers'
(: int-cmp : Integer Integer -> Order)
(define (int-cmp i1 i2)
    (cond
        [(< i1 i2) '<]
        [(> i1 i2) '>]
        [else '=]))
;;tree-int 
(define tree-int : (Binary-Tree Integer) 
  (Node
   (Node 'Empty 0 'Empty)
   1
   (Node 'Empty 2 'Empty)))
;;set
(define set-int ((inst Set Integer) int-cmp tree-int))
;; testing
(check-expect (between 0 3 set-int) '(1))

;;test with strings
(: string-cmp : (Cmp String))
;; comparisons on strings
(define (string-cmp s1 s2)
    (cond
        [(string<? s1 s2) '<]
        [(string>? s1 s2) '>]
        [else '=]))
        
;; tree defined separately for clarity
;;    "b"
;;   /   \
;; "a"   "c"
(define tree-abc : (Binary-Tree String) 
   (Node (Node 'Empty "a" 'Empty) "b" (Node 'Empty "c" 'Empty)))
   
(define set-abc : (Set String) (Set string-cmp tree-abc))
;;should pass test
(check-expect (between "a" "f" set-abc) (list "b" "c"))


;;(: remove-max : (All (T) (Binary-Tree T) -> (Pair T (Binary-Tree T))))
(: remove-max : (All (T) (Binary-Tree T) -> (Pair T (Binary-Tree T))))
(define (remove-max tree)
  (match tree
    ['Empty (Pair 'Empty 'Empty)]
    [(Node left y right)
     (local
       {(: go-right : (All (T) (Node T) -> T))
        (define (go-right tr)
          (match right
            ['Empty y]
            [(Node left y right) (go-right right)]))} (Pair (go-right tree)))]))

(test)