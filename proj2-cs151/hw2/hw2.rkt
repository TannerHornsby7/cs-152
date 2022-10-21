#lang typed/racket

;; CMSC15100 Winter 2022
;; Homework 2
;; Tanner Hornsby

;; include CS151-specific definitions
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;;Question 1: approximate pi
(: random-coord : -> Real)
;; return a random number in the range [-1 .. 1]
(define (random-coord) (- (* 2 (random)) 1))

;; A (Point x y) represents a point in the plane
;;
(define-struct Point
  ([x : Real]
   [y : Real]))
(: p1 : Point)
(: p2 : Point)

(define p1 (Point .5 .5))
(define p2 (Point 3 5))


;;First function: in-circle?
;;takes a Point argument representing a point ⟨x,y⟩ and returns #t if they are within the unit circle (i.e., x2+y2<1) and #f otherwise.)
(: in-circle? : Point -> Boolean)
(define (in-circle? p)
  (if (< (+ (* (Point-x p) (Point-x p)) (* (Point-y p) (Point-y p)) ) 1) #t #f))


;;Second function: count-in-circle
;;counts the number of random points that land within the unit circle.
;; Uses the random-coord function to generate the x and y coordinates of the points.

(: count-in-circle : Natural Natural -> Real)
;; the first argument is the number of points left to generate
;; and the second argument is the number of points in the circle so far
(define (count-in-circle n sum)
  (local
    {(: aux-count-in-circle : Natural Natural -> Real) 
     (define (aux-count-in-circle n sum)
     (if (= n 0) sum (count-in-circle (- n 1) (+ sum 1))))
     }
     (aux-count-in-circle n sum)
    )
  )

;;Third function: approximate pi
(: approximate-pi : Natural -> Real)
;;given a natural number n>0, approximates π by sampling n random points. If n=0, then signals an error
(define (approximate-pi n)
(if (> n 0) (* (/ n (count-in-circle n 0)) 4)
    (error "approximate-pi: argument must be at least one")))

;;Question 2
(define-struct Cubic
  ([a : Exact-Rational]
   [b : Exact-Rational]
   [c : Exact-Rational]
   [d : Exact-Rational]))

;;eval-cubic function
;;(: eval-cubic : Cubic Real -> Real)
;;;;(define (eval-cubic c x -> y)
  ;;(+ (* (Cubic-a c) x x x) (* (Cubic-b c) x x) (* (Cubic-c c) x) Cubic-d))
;;cubic test point
(: c1 : Cubic)
(define c1 (Cubic 1 2 3 4))

;;cubic-> string
(: cubic->string : Cubic -> String)
(define (cubic->string c)
  (string-append (number->string (Cubic-a c)) "*x^3 + " (number->string (Cubic-b c)) "*x^2 + "
                 (number->string (Cubic-c c)) "*x + " (number->string (Cubic-d c))))


;;derivative
(define-struct Quadratic
([a : Exact-Rational]
 [b : Exact-Rational]
 [c : Exact-Rational]))

(: derivative : Cubic -> Quadratic)
(define (derivative c)
(: q : Quadratic)
(define q (Quadratic
           (exact-ceiling (* 3.0 (Cubic-a c)))
           (* 2 (Cubic-b c))
           (Cubic-c c)))
  q)

;;Question 3
;;trinomial function
;;takes row and element indices (in that order) and returns the value at that location in the Trinomial triangle
;;trinomial row local function
;;takes a row index as an argument and returns the string representation of the given row in the Trinomial triangle
(: trinomial : Integer Integer -> Integer)
(define (trinomial r e)
  2)
(: trinomial-row : Integer -> String)
(define (trinomial-row r)
  (local
    {(: trinomial-row-aux : Integer Integer String -> String)
     (define (trinomial-row-aux i r prod)
       (cond [(= r 1) "1 1 1"]
             [(> r 1) "recursive case"]
             [else "else"]))}
    (trinomial-row-aux 0 r "1\n")
  ))
  

;; run tests
;;Question 1
;;-in-circle?
(check-expect (in-circle? p1) #t)
(check-expect (in-circle? p2) #f)

;;Question 2: Cubic Function Struct
(display (cubic->string c1))

;;Question 3: Pyramid thing

;;
(test)