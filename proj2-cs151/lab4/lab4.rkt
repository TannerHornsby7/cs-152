#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

;;Task 1: Playing Cards======================================================================================================================
(define-type Face (U 'Jack 'Queen 'King))
(define-type Suit (U 'Spades 'Hearts 'Clubs 'Diamonds))
(define-type Color (U 'red 'black))

(define-struct Pip-Card
    ([rank : Natural]
     [suit : Suit]))

(define-struct Face-Card
    ([rank : Face]
     [suit : Suit]))


(define-type Card (U Pip-Card Face-Card))

;;smart card constructor function
(: smart-pip : Natural Suit -> Pip-Card)
(define (smart-pip r s)
(if (<= r 10)
    (match s
      [Spades (Pip-Card r Spades)]
      [Hearts (Pip-Card r Hearts)]
      [Clubs (Pip-Card r Clubs)]
      [Diamonds (Pip-Card r Diamonds)]
      )
    (error "Please input a rank 1-10 and a suit of Spades, Heats, Clubs, or Diamonds")
    )
  )
;;(and (< r 10) (symbol=? s Suit))

;;card-color function
;;input card and return card color
(: card-color : Card -> Color)
(define (card-color c)
(match c
  [(Pip-Card _ _)
    (match Pip-Card-suit
      [Spades 'black]
      [Hearts 'red]
      [Clubs 'black]
      [Diamonds 'red]
      )]
  [(Face-Card _ _)
   (match Pip-Card-suit
      [Spades 'black]
      [Hearts 'red]
      [Clubs 'black]
      [Diamonds 'red]
     )]
  )
)
;;compare cards
;;Return true if and only if the two cards are the same.
;;Accomplish this by comparing their types and, if appropriate, their ranks and suits.
(: card=? : Card Card -> Boolean)
(define (card=? c1 c2)
  (match* (c1 c2)
    [((Face-Card r1 s1) (Face-Card r2 s2)) (and (symbol=? r1 r2) (symbol=? s1 s2))]
    [((Pip-Card r1 s1) (Pip-Card r2 s2)) (and (= r1 r2) (symbol=? s1 s2))]
    [((Face-Card _ _) (Pip-Card _ _)) #f]
    [((Pip-Card _ _) (Face-Card _ _)) #f]
  )
)
;;card->string
;;convert a cart to a string with the format:  "Ace of Spades", "4 of Hearts", "Jack of Diamonds".
(: card->string : Card -> String)
(define (card->string c1)
  (match c1
    [(Face-Card r s)
     (string-append (symbol->string r) " of " (symbol->string s))]
    [(Pip-Card r s)
     (string-append (if (> r 1) (number->string r) "Ace") " of " (symbol->string s))]
    )
  )

;;Task 2: Making Change======================================================================================================================
;;If there are no relevant limitations on available coins, the best algorithm for making change
;;(in the sense that it uses the fewest coins) is as follows:
;;keep dispensing quarters until you would go over the desired amount of change,
;;then keep dispensing dimes for the remaining change, and then do the same with nickels,
;;finally issuing pennies as needed.

(define-struct Coins
    ([quarters : Natural]
     [dimes : Natural]
     [nickels : Natural]
     [pennies : Natural]))

;;function logic
;;recursive function which repeats until sum<=5.
;;sum-aux(sum i=sum n=0 prod=sum)
;;if (sum<=5) (Coins q d n sum)
;;if (5<=sum<10) (Coins q d sum p)
;;If sum>=25 then sum = sum % 25 & quarters = sum / 25,
;;If 25>=sum>=10 then sum= sum % 10 & dimes = sum / 10,
;;If 10>=sum>=5 then sum= sum % 5 & dimes = sum / 5,
;;else pennies = sum.
;;helper function that takes total number of cents and coin in quesiton

(: aux-coin-remainder : Natural Natural -> Natural)
(define (aux-coin-remainder amt coin)
  (remainder amt coin))
(: aux-coin-divider : Natural Natural -> Natural)
(define (aux-coin-divider amt coin)
  (quotient amt coin))

;;(: aux-recursive-coin-function : Natural -> Natural)
  ;(define (aux-recursive-coin-function amt)
    
   ; (define C (Coins 0 0 0 0))
;    (match C
;      [(Coins q d n p) (if (<= amt 0) 
;                        (error "please input a value greater than 0")
;                        (Coins
;                         (aux-recursive-coin-function (remainder amt 25))
;                         (aux-recursive-coin-function (remainder amt 10)) 
;                         (aux-recursive-coin-function (remainder amt 5))
;                         (aux-recursive-coin-function (remainder amt 1)))]))
      

(: make-change : Integer -> Coins)
(define (make-change sum)
  (define c (Coins 0 0 0 0))
  (match c
    [(Coins q d n p) (if (<= sum 0) 
                        (error "please input a value greater than 0")
                        (Coins
                         (aux-coin-divider sum 25)
                         (aux-coin-divider (aux-coin-remainder sum 25) 10) 
                         (aux-coin-divider (aux-coin-remainder (aux-coin-remainder sum 25) 10) 5)
                         (aux-coin-remainder (aux-coin-remainder (aux-coin-remainder sum 25) 10) 5)))]))

;;Task 3: Nats===============================================================================================================================

(define-type Nat (U 'Z S))
(define-struct S
    ([pred : Nat]))

;;(S (S (S 'Z))) to 3
(: nat->natural : Nat -> Natural)
(define (nat->natural n)
  (match n
    [(S p) (+ (nat->natural p) 1)]
    [_ 0]))

;;3 to (S (S (S 'Z)))
(: natural->nat : Natural -> Nat)
(define (natural->nat n)
  (if (< 0 n)
        (S (natural->nat (- n 1)))
        'Z)
   )


;;Task 1 TESTS: Playing Cards======================================================================================================================
;;card declarations
(define card1 (Pip-Card 3 'Spades))
(define card2 (Pip-Card 3 'Spades))
(define card3 (Face-Card 'Jack 'Hearts))

;;smart card constructor function test
(check-expect (smart-pip 3 'Spades) (Pip-Card 3 'Spades))
;;card color return function test
(check-expect (card-color (Pip-Card 3 'Spades)) 'black)
;;card comparison function test
(check-expect (card=? card1 card2) #t)
(check-expect (card=? card1 card3) #f)
;;card to string function test
(display (card->string card1))
(display (card->string card2))
(display (card->string card3))

;;Task 2 TEST: Making Change======================================================================================================================
;;make-change function tests
(check-expect (make-change 43) (Coins 1 1 1 3))
;(check-expect (aux-recursive-coin-function 43) (Coins 1 1 1 3))


;;Task 3 TESTS: Nats==============================================================================================================================
(check-expect (nat->natural (S (S (S 'Z)))) 3)
(check-expect (nat->natural (S (S (S (S (S (S 'Z))))))) 6)
(check-expect (natural->nat 6) (S (S (S (S (S (S 'Z)))))))
(display (natural->nat 1))

(test)