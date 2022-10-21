#lang typed/racket

;; CMSC15100 Winter 2022
;; Homework 5
;; Tanner Hornsby

;; include CS151-specific definitions
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;; An (Option T) is either 'None or (Some v), where v has type T
(define-type (Option T) (U 'None (Some T)))
(define-struct (Some T) ([value : T]))

;; A (Pair a b) represents a pair of values
(define-struct (Pair A B)
  ([fst : A]
   [snd : B]))

;; ====================
;; Problem 1
;; ==========

;; a vector representation of a complete binary tree
(define-type (VTree A) (Vectorof A))

;; vtree-empty?

;; valid-index

;; vtree-left

;; vtree-right

;; vtree-parent

;; vtree-rightmost
;;vtree-left : (All (A) (VTree A) -> Natural -> (Option Natural))

;;returns the index of the specified node’s left child, or 'None if there is no left child. You may assume that the argument index you are given is valid for the tree.
;; A recursive representation of binary trees
(define-type (Tree A) (U 'Empty (Node A)))
(define-struct (Node A)
  ([left  : (Tree A)]   ;; left child
   [val   : A]          ;; value at this node
   [right : (Tree A)])) ;; right child

;;vtree-empty?
(: vtree-empty? : (All (A) (VTree A) -> Boolean))
;;returns true if the argument tree is empty and false otherwise
(define (vtree-empty? tree)
  (= (vector-length tree) 0))

;;testing vtree
(check-expect (vtree-empty? (vector)) #t)
(check-expect (vtree-empty? (vector 1)) #f)
(check-expect (vtree-empty? (vector 1 2 7 100)) #f)(check-expect (vtree-empty? (vector 1)) #f)


;;v-tree left
(: vtree-left : (All (A) (VTree A) -> Natural -> (Option Natural)))
;;returns the index of the specified node’s left child,
;;or 'None if there is no left child. You may assume that the argument index you are given is valid for the tree.
(define (vtree-left tree)
  (lambda ([i : Natural])
    (if (< 0 (+ 1 (* 2 i)) (vector-length tree))
        (Some (+ 1 (* 2 i)))
        'None)))

;;testing left
;;2i+1
;;2*0+1=1
(check-expect
 ((vtree-left (vector 0 1 2)) 0) (Some 1))

;;vtree-right
(: vtree-right : (All (A) (VTree A) -> Natural -> (Option Natural)))
;;returns the index of the specified node’s left child,
;;or 'None if there is no left child. You may assume that the argument index you are given is valid for the tree.
(define (vtree-right tree)
  (lambda ([i : Natural])
    (if (< 0 (+ 2 (* 2 i)) (vector-length tree))
        (Some (+ 2 (* 2 i)))
        'None)))

;;testing vtree-right
;;2i+1
;;2*0+1=1
(check-expect
 ((vtree-right (vector 0 1 2)) 0) (Some 2))

;;v-tree parent
(: vtree-parent : (All (A) (VTree A) -> Natural -> (Option Natural)))
;;returns the index of the specified node’s parent, or 0 if the node is the root.
;;You may assume that the argument index you are given is valid for the tree.
(define (vtree-parent tree)
  (lambda ([i : Natural])
    (cond
      [(= i 0) (Some 0)]
      [(or (= i 1) (= i 2)) (Some 0)]
      [(= (remainder i 2) 0)
       ;;right subtree
       (Some (quotient i 2))]
      [else
       ;;left subtree
       (Some (quotient (- i 1) 2))])))
(check-expect ((vtree-parent (vector 0 1 2)) 2) (Some 0))
(check-expect ((vtree-parent (vector 0 1 2)) 1) (Some 0))
(check-expect ((vtree-parent (vector 0 1 2)) 0) (Some 0))

;;vtree-rightmost
(: vtree-rightmost : (All (A) (VTree A) -> (Option A)))
(define (vtree-rightmost tree)
  (if (vtree-empty? tree)
      'None
      (local
        {(: go-right : Natural -> (Option A))
         (define (go-right index)
           (match ((vtree-right tree) index)
             ['None (Some (vector-ref tree index))]
             [(Some i) (go-right i)]))}
        (go-right 0))))

(check-expect (vtree-rightmost (vector)) 'None)
(check-expect (vtree-rightmost (vector 0)) (Some 0))
(check-expect (vtree-rightmost (vector 0 1)) (Some 0))
(check-expect (vtree-rightmost (vector 0 1 3)) (Some 3))

;;vtree->tree
(: vtree->tree : (All (A) (VTree A) -> (Tree A)))
;;turn a vector tree into a tree
(define (vtree->tree tree)
  (if (vtree-empty? tree)
      'Empty
      (local
        {(: vtree-helper : (Option Natural) -> (Tree A))
         (define (vtree-helper index)
           (match index
             [(Some i) (Node
                        (vtree-helper ((vtree-left tree) i))
                        (vector-ref tree i)
                        (vtree-helper ((vtree-right tree) i)))]
             ['None 'Empty]))}
        ;;we want to end when ((vtree-parent tree) index) = (Some 0), return Tree.
        (vtree-helper (Some 0)))))

(check-expect (vtree->tree (vector)) 'Empty)
(check-expect (vtree->tree (vector 0 1 2)) (Node (Node 'Empty 1 'Empty) 0 (Node 'Empty 2 'Empty)))
(test)

;; ====================
;; Problem 2
;; ==========

(: vector-foldl : (All (X Y) (X Y -> Y) Y (Vectorof X) -> Y))
;; fold the function f over the vector's elements from left to right
(define (vector-foldl f init v)
  (local
    {(: fold : Integer Y -> Y)
     ;; helper function that iterates over the vector indices
     (define (fold i acc)
       (if (< i (vector-length v))
           (fold (+ i 1) (f (vector-ref v i) acc))
           acc))}
    (fold 0 init)))


;; == Graphs

;; a directed graph is represented as a vector of nodes
(define-type (Graph A) (Vectorof (GNode A)))

;; a (GNode id attr succs) represents a node in a directed graph,
;; where the id is a unique identifier, attr is the attribute value
;; stored at the node, and succs is a list of successor-node indices.
(define-struct (GNode A)
  ([id : Natural]
   [attr : A]
   [succs : (Listof Natural)]))

(: successors-of : (All (A) (Graph A) -> (GNode A) -> (Listof (GNode A))))
;; map a node to its successors
(define (successors-of g)
  (lambda ([nd : (GNode A)])
    (match nd
      [(GNode _ _ succs)
       (map (lambda ([i : Natural]) (vector-ref g i)) succs)])))

(: node=? : (All (A) (GNode A) (GNode A) -> Boolean))
;; are two nodes the same?
(define (node=? nd1 nd2)
  (= (GNode-id nd1) (GNode-id nd2)))


;; == Rose Trees

;; A (RTree v kids) is a node in a Rose Tree, where v is the value
;; associated with the node and kids is a list of the children of
;; the node.
(define-struct (RTree A)
  [(val : A)
   (kids : (Listof (RTree A)))])

(define-type (Spanning-Tree A) (RTree (GNode A)))
(define-type (Spanning-Forest A) (Listof (Spanning-Tree A)))

;; spanning-forest(Pair (Listof (GNode A)) (Spanning-Forest A))

;; example graph from lecture
(define G : (Graph Symbol)
  (vector
   (GNode 5 'A '(1 3))    ;; A -> B; D
   (GNode 2 'B '(3))      ;; B -> D
   (GNode 8 'C '(1 4 5))  ;; C -> B; E; F
   (GNode 0 'D '(4 6 7))  ;; D -> E; G; H
   (GNode 3 'E '(1 6))    ;; E -> B; H
   (GNode 7 'F '(5))      ;; F -> F
   (GNode 6 'G '())       ;; G ->
   (GNode 1 'H '())))     ;; H ->



;; expected result of (spanning-forest G)
#|
(list
 (RTree (GNode 5 'A '(1 3))
        (list
         (RTree (GNode 2 'B '(3))
                (list
                 (RTree (GNode 0 'D '(4 6 7))
                        (list
                         (RTree (GNode 3 'E '(1 6))
                                (list
                                 (RTree (GNode 6 'G '()) '())))
                         (RTree (GNode 1 'H '()) '())))))))
 (RTree (GNode 8 'C '(1 4 5))
        (list
         (RTree (GNode 7 'F '(5)) '()))))
|#

;; Spanning Forrest Function
(: spanning-forrest : (All (A) (Graph A) -> (Spanning-Forest A)))
;;creates a spanning forrest from a graph
(define (spanning-forrest g)
  ;;(local
  (local
    {(define succs (successors-of g))
     (: visited? : (GNode A) (Pair (Listof (GNode A)) (Spanning-Forest A))  -> Boolean)
     (define (visited? nd pr) (ormap (lambda ([x : (GNode A)]) (node=? nd x)) (Pair-fst pr)))
     ;     (: gnode-succs->listofRTrees : (GNode A) -> (Listof (RTrees (GNode A))))
     ;     ;;given a gnode, returns a list of RTrees of the GNodes successors(children). 
     ;     (define (gnode-succs->listofRTrees node)
     ;       (map (lambda ([x : (GNode A)]) (RTree (GNode-attr nd)   (succs nd)
     ;     (: next-frontier : Frontier -> Frontier)
     ;     ;; given a List of GNodes, compute a new frontier by taking one
     ;     ;; step forward
     ;     (define (next-frontier frontier)
     ;       (foldl
     ;        (lambda ([nd : Node] [f : Frontier]) (append (next nd) f))
     ;        ’()
     ;        frontier))
;     (: node->RTree : (GNode A) -> (RTree (GNode A)))
;     (define (node->RTree node)
;       (match (succs node)
;         ['Empty (RTree node 'Empty)]
;         [_ ((RTree node (map node->RTree (succs node))))]))

       ;;
       (: dfs : (GNode A) (Pair (Listof (GNode A)) (Spanning-Forest A)) -> (Pair (Listof (GNode A)) (Spanning-Forest A)))
       ;; visit nd and add its RTree of children to visited if it isn’t already in the list of visited nodes
       (define (dfs nd pair)
         (if (visited? nd pair)
             pair
             (foldl dfs (Pair (cons nd (Pair-fst pair)) (Pair-snd pair)) (succs nd))
               [(Pair list tree) (Pair (cons nd list) (cons (RTree nd '()) tree))])))}
(reverse (Pair-snd (vector-foldl dfs (Pair '() '()) g)))))

;;check-expect
(define TestGraph : (Graph Symbol)
  (vector
   (GNode 5 'A '(1 3))    ;; A -> B; D
   (GNode 2 'B '(3))      ;; B -> D
   (GNode 8 'C '(1 4 5))  ;; C -> B; E; F
   (GNode 0 'D '(4 6 7))  ;; D -> E; G; H
   (GNode 3 'E '(1 6))    ;; E -> B; G
   (GNode 7 'F '(5))      ;; F -> F
   (GNode 6 'G '())       ;; G ->
   (GNode 1 'H '())))     ;; H ->

(check-expect (spanning-forrest TestGraph) (list
 (RTree (GNode 5 'A '(1 3))
        (list
         (RTree (GNode 2 'B '(3))
                (list
                 (RTree (GNode 0 'D '(4 6 7))
                        (list
                         (RTree (GNode 3 'E '(1 6))
                                (list
                                 (RTree (GNode 6 'G '()) '())))
                         (RTree (GNode 1 'H '()) '())))))))
 (RTree (GNode 8 'C '(1 4 5))
        (list
         (RTree (GNode 7 'F '(5)) '())))))
(test)
