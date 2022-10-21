#lang typed/racket

;; CMSC15100 Winter 2022
;; Homework 3
;; <YOUR NAME HERE>

;; include CS151-specific definitions
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;;==============================

;; An operator is either integer addition ('+), integer multiplication ('*),
;; integer less-than ('<), or integer equality ('=)
;;
(define-type Operator (U '+ '* '< '=))

;; An Exp is a representation of simple expressions and is either
;; a binary expression, a conditional expression, an integer
;; constant, or a boolean constant
;;
(define-type Exp (U Bin-Exp If-Exp Int-Exp Bool-Exp))

;; A (Bin-Exp op e1 e2) represents a binary expression with
;; operator op, and arguments e1 and e2
;;
(define-struct Bin-Exp
  ([op : Operator]
   [arg1 : Exp]
   [arg2 : Exp]))

;; An (If-Exp tst e1 e2) represents a conditional expression
;; where tst is the boolean-valued test,
(define-struct If-Exp
  ([test : Exp]
   [then-expr : Exp]
   [else-expr : Exp]))

;; An (Int-Exp n) represents the integer value n
(define-struct Int-Exp [(value : Integer)])

;; A (Bool-Exp b) represents the boolean value b
(define-struct Bool-Exp [(value : Boolean)])

(: not-exp : Exp -> Exp)
;; synthesize an expression for the logical negation of the
;; argument expression
(define (not-exp e)
  (If-Exp e (Bool-Exp #f) (Bool-Exp #t)))

(check-expect (not-exp (Bin-Exp '< (Int-Exp 17) (Int-Exp 42)))
              (If-Exp (Bin-Exp '< (Int-Exp 17) (Int-Exp 42))
                      (Bool-Exp #f)
                      (Bool-Exp #t)))

;;==============================
;;PROBLEM ONE: SYNTACTIC SUGAR
;;our new expression language defined above doesnt possess logical operators and and or, write them below:

;;or logical expression function
(: or-exp : Exp Exp -> Exp)
(define (or-exp e1 e2)
  (If-Exp e1
             (Bool-Exp #t)
             (If-Exp e2
                    (Bool-Exp #t)
                    (Bool-Exp #f))))

(check-expect (or-exp (Bin-Exp '< (Int-Exp 2) (Int-Exp 3)) (Bin-Exp '< (Int-Exp 4) (Int-Exp 5)))
                (If-Exp (Bin-Exp '< (Int-Exp 2) (Int-Exp 3))
                        (Bool-Exp #t)
                        (If-Exp (Bin-Exp '< (Int-Exp 4) (Int-Exp 5))
                                (Bool-Exp #t)
                                (Bool-Exp #f))))              

;;and logical expression function
(: and-exp : Exp Exp -> Exp)
(define (and-exp e1 e2)
  (If-Exp e1
             (If-Exp e2
                    (Bool-Exp #t)
                    (Bool-Exp #f))
             (Bool-Exp #f)))

(check-expect (and-exp (Bin-Exp '< (Int-Exp 2) (Int-Exp 3)) (Bin-Exp '< (Int-Exp 4) (Int-Exp 5)))
                 (If-Exp (Bin-Exp '< (Int-Exp 2) (Int-Exp 3))
                         (If-Exp
                            (Bin-Exp '< (Int-Exp 4) (Int-Exp 5))
                                 (Bool-Exp #t)
                                 (Bool-Exp #f))
                            (Bool-Exp #f)))

;;leq logical expression function
(: leq : Exp Exp -> Exp)
(define (leq e1 e2)
  (or-exp (Bin-Exp '< e1 e2) (Bin-Exp '= e1 e2)))

(check-expect (leq (Int-Exp 3) (Int-Exp 5)) 

               (or-exp (Bin-Exp '<(Int-Exp 3) (Int-Exp 5)) (Bin-Exp '= (Int-Exp 3) (Int-Exp 5))))

;;Problem 2: Evaluation================================================================================================

(define-type Result (U Int-Exp Bool-Exp))
(: eval : Exp -> Result)
(define (eval e)
  (match e
  [(Bool-Exp b) e]
  [(Int-Exp n) e]
  ;;[(If-Exp e a1 a2) 
  [(Bin-Exp o a b) (match* (a b)
                     [((Bool-Exp _)(Bool-Exp _)) (error "eval: type error")]
                     [((Int-Exp n1)(Int-Exp n2))
                      (match o
                        ['< (Bool-Exp (< n1 n2))]
                        ['= (Bool-Exp (= n1 n2))]
                        ['+ (Int-Exp (+ n1 n2))]
                        ['* (Int-Exp (* n1 n2))])])]))


;;checks
;;(display (eval (Bin-Exp '+ (Int-Exp 1) (Int-Exp 2))))
(check-expect (eval (Int-Exp 17)) (Int-Exp 17))
(check-expect (eval (Bin-Exp '< (Int-Exp 17) (Int-Exp 42))) (Bool-Exp #t))

;;Problem 3=======================================================================================================================================
;; The expression-language type of an `Exp` is either 'int,
;; 'bool, or 'error, with the latter value signifying a type
;; error.
(define-type Ty (U 'int 'bool 'error))

;;create (check-bin-op '< 'int 'int)
(: check-bin-op : Operator Ty Ty -> Ty)
(define (check-bin-op op arg1 arg2)
  (match* (op arg1 arg2)
    [('< 'int 'int) 'bool]
    [('= 'int 'int) 'bool]
    [('* 'int 'int) 'int]
    [('+ 'int 'int) 'int]
    [(_ _ _) 'error]))


(check-expect (check-bin-op '< 'int 'int) 'bool)
(check-expect (check-bin-op '+ 'int 'int) 'int)
(check-expect (check-bin-op '+ 'bool 'int) 'error)
(check-expect (check-bin-op '* 'int 'error) 'error)

;;typecheck takes an exp and returns the type
(: typecheck : Exp -> Ty)
(define (typecheck e)
  (match e
    [(Bool-Exp _) 'bool]
    [(Int-Exp _) 'int]
    [(Bin-Exp o a b) (match* (a b)
                     [((Bool-Exp _)(Bool-Exp _)) (error "eval: type error")]
                     [((Int-Exp n1)(Int-Exp n2))
                      (match o
                        ['< 'bool]
                        ['= 'bool]
                        ['+ 'int]
                        ['* 'int])])]))

(check-expect (typecheck (Int-Exp 1)) 'int)
(check-expect (typecheck (Bin-Exp '+ (Int-Exp 1) (Int-Exp 1))) 'int)
(check-expect (typecheck (Bin-Exp '= (Int-Exp 1) (Int-Exp 1))) 'bool)

;;Problem 4: Print=====================================================================================================================================
;;define a print funtion which prints exp p as a string

;;You can use the symbol->string function to convert Operator values to their string equivalents.
;;You will find number->string useful for printing Int-Exp expressions, but
;;Racket does not have a function for converting Boolean values to strings.

(: exp->string : Exp -> String)
(define (exp->string e)
  (string-append "" (match e
    [(Bool-Exp b) (if b "true" "false")]
    [(Int-Exp n) (number->string n)]
    [(If-Exp test then else) (string-append "(if " (exp->string test)" " (exp->string then) " " (exp->string else) ") ")]
    [(Bin-Exp o a b) (match* (a b)
                     [((Bool-Exp _)(Bool-Exp _)) (error "eval: type error")]
                     [((Int-Exp n1)(Int-Exp n2)) (string-append "(" (symbol->string o) " " (number->string n1) " " (number->string n2) " )")])])))

;; "(if " (exp->string test) " ( " (exp->string then) " ) ( " (exp->string else
;(check-expect
;  (exp->string
;    (If-Exp (Bin-Exp '< (Int-Exp 1) (Int-Exp 2))
;            (Bin-Exp '* (Int-Exp 2) (Int-Exp 3))
;            (Bin-Exp '+ (Int-Exp 4) (Int-Exp 5))))
;  "(if (< 1 2) (* 2 3) (+ 4 5))")

;;(display (exp->string (Bool-Exp #f)))
;;(display (exp->string (Int-Exp 1000)))
(display (exp->string (If-Exp (Bin-Exp '< (Int-Exp 1) (Int-Exp 2))
                              (Bin-Exp '* (Int-Exp 2) (Int-Exp 3))
                              (Bin-Exp '+ (Int-Exp 4) (Int-Exp 5)))))

  
;;
(test)
