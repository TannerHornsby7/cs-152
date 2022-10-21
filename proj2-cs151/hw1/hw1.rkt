#lang typed/racket

;; CMSC15100 Winter 2022
;; Homework 1
;; <Tanner Hornsby>

;; include CS151-specific definitions
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;; YOUR CODE HERE Delete this when done
;;problem 1: eval-quadratic
;;the following code evaluates a quadratic function with the variables and constants given as parameters
(: eval-quadratic : Real Real Real Real -> Real)
(define (eval-quadratic a b c x)
  (+ (* a (* x x)) (* x b) c))

;;problem 2: within?
;;determines whether two inputs, x & y, are within a specified range, z of each other.
(: within? : Real Real Real -> Boolean)
(define (within? x y z)
  (cond [(<= (abs (- y x)) z)]
        [else #f]))

;;problem 3: on-quadratic?
;;determines if a given x,y is within range z of quadratic (x, f(x))
(: on-quadratic : Real Real Real Real Real Real -> Boolean)
(define (on-quadratic a b c x y z)
(within? (eval-quadratic a b c x) y z))

;;problem 4: pythagorean?
;;code that determines if a given trio of numbers is a pythagorean group returns true or false
(: pythagorean? : Real Real Real -> Boolean)
(define (pythagorean? a b c)
  (= (+ (* a a) (* b b)) (* c c)))

;;problem 5: motzkin
;;recursive code which completes the motzkin sequence for a given number n
(: motzkin : Integer -> Exact-Rational)
(define (motzkin n)
  (cond [(< n 0) 0]
    [(or (= n 0) (= n 1)) 1]
        [else (+(*(/(+(* 2 n) 1) (+ n 2)) (motzkin (- n 1))) (*(/(-(* 3 n) 3) (+ n 2)) (motzkin (- n 2))))]))

;;problem 6: base3-string
;;turns integer into representative base3 string of characters
(: nat->base3-string : Integer -> String)
(define (nat->base3-string n)
(cond
[(= n 0) "0"]
[(= n 1) "1"]
[(= n 2) "2"]
[(= (remainder n 3) 0)
(string-append (nat->base3-string (quotient n 3)) "0")]
[(= (remainder n 3) 1)
(string-append (nat->base3-string (quotient n 3)) "1")]
[else (string-append (nat->base3-string (quotient n 3)) "2")] ))
                 

;; run tests

;;problem 1: eval-quadratic
(check-expect (eval-quadratic 1 1 1 2) 7)
(check-expect (eval-quadratic 0 0 0 0) 0)

;;problem 2: within?
(check-expect (within? 1 2 100) #t)
(check-expect (within? 1 100 2) #f)

;;problem 3: on-quadratic?
(check-expect (on-quadratic 1 1 1 2 7 10) #t)
(check-expect (on-quadratic 0 0 0 0 10 1) #f)

;;problem 4: pythagorean?
(check-expect (pythagorean? 3 4 5) #t)
(check-expect (pythagorean? 100 100 5) #f)

;;problem 5: motzkin
(check-expect (motzkin 0) 1)
(check-expect (motzkin 1) 1)
(check-expect (motzkin 2) 2)
(check-expect (motzkin -1) 0)

;;problem 6: base3-string
(check-expect (nat->base3-string 9) "100")
(check-expect (nat->base3-string 11) "102")
;;
(test)