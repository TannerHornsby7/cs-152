#lang typed/racket

(require typed/test-engine/racket-tests)

(require "../include/cs151-core.rkt")

;;Definitions
(define-type Face (U 'Jack 'Queen 'King))
(provide Face)
(define-type Suit (U 'Spades 'Hearts 'Clubs 'Diamonds))
(provide Suit)
(define-type Color (U 'red 'black))
(provide Color)


(define-struct Pip-Card
    ([rank : Natural]
     [suit : Suit]))
(provide (struct-out Pip-Card))

(define-struct Face-Card
    ([rank : Face]
     [suit : Suit]))
(provide (struct-out Face-Card))


(define-type Card (U Pip-Card Face-Card))
(provide Card)

;; Cards To Colors Function
(: cards->colors : (Listof Card) -> (Listof Color))
;; takes a list of cards and returns a list of their colors in the same order
(define (cards->colors L)
  (local
    {(: aux->color : Card -> Color)
        (define (aux->color x)
          (if (Pip-Card? x)
                     (match (Pip-Card-suit x)
                       ['Hearts 'red]
                       ['Diamonds 'red]
                       [_ 'black])
                     (match (Face-Card-suit x)
                       ['Hearts 'red]
                       ['Diamonds 'red]
                       [_ 'black])))}
    (map aux->color L)))
(provide cards->colors)
;;TESTS
;;test list one (standard list)
(define inColorCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
(define outColorCardList1 (list 'red 'black 'red))
;;test list two (one element list)
(define inColorCardList2 (list (Face-Card 'King 'Hearts)))
(define outColorCardList2 (list 'red))

;;check expect statements
(check-expect (cards->colors inColorCardList1) outColorCardList1)
(check-expect (cards->colors inColorCardList2) outColorCardList2)


;;Cards To Points
(: cards->points : (Listof Card) -> (Listof Natural))
;;given a list of cards, return a list of their respective point values using the translation below:
;;Face cards will be worth ten points; pip cards will be worth their numerical rank.
;;For instance, the seven of spades will be worth seven points, and the ace of diamonds, one.
(define (cards->points L)
  (local
    {(: aux->points : Card -> Natural)
        (define (aux->points x)
          (if (Pip-Card? x)
                     (match x
                       [(Pip-Card r s) r])
                     10))}
    (map aux->points L)))
(provide cards->points)
;;TESTS
;;test list one (standard list)
(define inPointCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
(define outPointCardList1 (list 10 2 10))
;;test list two (one element list)
(define inPointCardList2 (list (Face-Card 'King 'Hearts)))
(define outPointCardList2 (list 10))

;;check expect statements
(check-expect (cards->points inPointCardList1) outPointCardList1)
(check-expect (cards->points inPointCardList2) outPointCardList2)

;;Filter Face Cards Function
(: face-cards : (Listof Card) -> (Listof Card))
;;Given a list of cards, produce a list of only the face cards in the list,
;;keeping them in the same relative order but skipping over any pip cards.
(define (face-cards L)
  (filter Face-Card? L))
(provide face-cards)
;;TESTS
;;test list one (standard list)
(define inFFaceCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
(define outFFaceCardList1 (list (Face-Card 'Jack 'Diamonds) (Face-Card 'Queen 'Hearts)))
;;test list two (one element list)
(define inFFaceCardList2 (list (Face-Card 'King 'Hearts)))
(define outFFaceCardList2 (list (Face-Card 'King 'Hearts)))
;;test list three (empty list)
(define inFFaceCardList3 '())
(define outFFaceCardList3 '())
;;check expect statements
(check-expect (face-cards inFFaceCardList1) outFFaceCardList1)
(check-expect (face-cards inFFaceCardList2) outFFaceCardList2)
(check-expect (face-cards inFFaceCardList3) outFFaceCardList3)

;;Filter Suit Function
(: cards-of-suit : Suit (Listof Card) -> (Listof Card))
;;Similar to the previous function, but instead produce a
;;list of cards from the original list that belong to the specified suit.
(define (cards-of-suit s L)
  (local
    {(: suit=? : Card -> Boolean)
     ;;compares the given suit with the suit of a given card
     (define (suit=? c)
       (match c
         [(Pip-Card _ sn) (symbol=? s sn)]
         [(Face-Card _ sn)(symbol=? s sn)]))}
    (filter suit=? L)))
(provide cards-of-suit)
;;TESTS
;;test list one (standard list)
(define inFSuitCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
(define outFSuitCardList1 (list (Pip-Card 2 'Clubs)))
;;test list two (one element list)
(define inFSuitCardList2 (list (Face-Card 'King 'Hearts)))
(define outFSuitCardList2 '())
;;test list three (empty list)
(define inFSuitCardList3 '())
(define outFSuitCardList3 '())
;;check expect statements
(check-expect (cards-of-suit 'Clubs inFSuitCardList1) outFSuitCardList1)
(check-expect (cards-of-suit 'Diamonds inFSuitCardList2) outFSuitCardList2)
(check-expect (cards-of-suit 'Hearts inFSuitCardList3) outFSuitCardList3)

;;All Red Function
(: all-red? : (Listof Card) -> Boolean)
;;Return true if and only if all the cards in the list are red.
(define (all-red? L)
  (and
   (= (+ (length (cards-of-suit 'Hearts L))
                    (length (cards-of-suit 'Diamonds L)))
                 (length L))
   (> (length L) 0)))
(provide all-red?)

;;TESTS
;;test list one (standard list)
(define inAllRCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
;;test list two (one element list)
(define inAllRCardList2 (list (Face-Card 'King 'Hearts)))
;;test list three (empty list)
(define inAllRCardList3 '())
;;test list four (long heterogenous list)
(define inAllRCardList4 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Diamonds)
                               (Face-Card 'Queen 'Diamonds)
                               (Pip-Card 7 'Diamonds)
                               (Pip-Card 2 'Hearts)
                               (Face-Card 'Queen 'Hearts)
                               ))
;;check expect statements
(check-expect (all-red? inAllRCardList1) #f)
(check-expect (all-red? inAllRCardList2) #t)
(check-expect (all-red? inAllRCardList3) #f)
(check-expect (all-red? inAllRCardList4) #t)

;;In Hand Function
(: in-hand? : Card (Listof Card) -> Boolean)
;;Return true if and only if at least one of the cards in the list matches the specified card.
(define (in-hand? c1 L)
  (local
    {(: card=? : Card -> Boolean)
     (define (card=? c2)
       (match* (c1 c2)
         [((Face-Card r1 s1) (Face-Card r2 s2)) (and (symbol=? r1 r2) (symbol=? s1 s2))]
         [((Pip-Card r1 s1) (Pip-Card r2 s2)) (and (= r1 r2) (symbol=? s1 s2))]
         [((Face-Card _ _) (Pip-Card _ _)) #f]
         [((Pip-Card _ _) (Face-Card _ _)) #f]))}
    (ormap card=? L)))
(provide in-hand?)
;;TESTS
;;test list one (standard list)
(define inIHandCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
;;test list two (one element list)
(define inIHandtCardList2 (list (Face-Card 'King 'Hearts)))
;;test list three (empty list)
(define inIHandCardList3 '())
;;check expect statements
(check-expect (in-hand? (Pip-Card 3 'Clubs) inIHandCardList1) #f)
;;(check-expect (in-hand? (Face-Card 'King 'Hearts) inIHandCardList2) #t)
(check-expect (in-hand? (Face-Card 'King 'Hearts) inIHandCardList3) #f)

;;Whole Suit Function
(: whole-suit : Suit -> (Listof Card))
;;Produce a list of the thirteen cards in a suit, in the order ace,
;;two through ten, jack, queen, king.
;;Neither use recursion nor hardcode a lengthy list by hand.
(define (whole-suit s)
  (local
    {(: suit-builder : Natural -> Card)
     (define (suit-builder n)
       (if (< n 10)
           (Pip-Card (+ n 1) s)
           (if (= n 10)
               (Face-Card 'Jack s)
               (if (= n 11)
                   (Face-Card 'Queen s)
                   (Face-Card 'King s)))))}
               (build-list 13 suit-builder)))
(provide whole-suit)
;;TESTS
;;test suit spades
(define outWSuitCardList1 (list 
                               (Pip-Card  1 'Spades)
                               (Pip-Card  2 'Spades)
                               (Pip-Card  3 'Spades)
                               (Pip-Card  4 'Spades)
                               (Pip-Card  5 'Spades)
                               (Pip-Card  6 'Spades)
                               (Pip-Card  7 'Spades)
                               (Pip-Card  8 'Spades)
                               (Pip-Card  9 'Spades)
                               (Pip-Card  10 'Spades)
                               (Face-Card  'Jack 'Spades)
                               (Face-Card  'Queen 'Spades)
                               (Face-Card  'King 'Spades)
                               ))
;;test suit hearts
(define outWSuitCardList2 (list 
                               (Pip-Card  1 'Hearts)
                               (Pip-Card  2 'Hearts)
                               (Pip-Card  3 'Hearts)
                               (Pip-Card  4 'Hearts)
                               (Pip-Card  5 'Hearts)
                               (Pip-Card  6 'Hearts)
                               (Pip-Card  7 'Hearts)
                               (Pip-Card  8 'Hearts)
                               (Pip-Card  9 'Hearts)
                               (Pip-Card  10 'Hearts)
                               (Face-Card  'Jack 'Hearts)
                               (Face-Card  'Queen 'Hearts)
                               (Face-Card  'King 'Hearts)
                               ))

;;check expect statements
(check-expect (whole-suit 'Spades) outWSuitCardList1)
(check-expect (whole-suit 'Hearts) outWSuitCardList2) 

;;Sorted? Function
(: sorted? : (Card Card -> Boolean) (Listof Card) -> Boolean)
;;take in a list of cards and return true if and only if that list is sorted.
;;a list is considered to be sorted if the function returns true for all (cn cn+1)
;;we consider a list with consecutive repetitions of cards to be unsorted for this function
(define (sorted? funct L)
;;use recursion to compare two values in a list and return true if all elements in the list adhere to the function equality.
;;(helper recursive function that takes in Listof Card outputs Listof Boolean
  (match L
    [(cons x '()) #t]
    [(cons x xr) (if (funct x (first xr)) (sorted? funct xr) #f)]
    [_ #t]))
(provide sorted?)
  
;;TESTS
;;test function and list one
(define inSortedCardList1 (list (Face-Card 'Jack 'Diamonds)
                               (Pip-Card 2 'Clubs)
                               (Face-Card 'Queen 'Hearts)))
(define inSortedCardList2 (list
                           (Pip-Card 3 'Clubs)
                           (Pip-Card 2 'Clubs)
                           (Pip-Card 1 'Clubs)))
                           
(: card=? : Card Card -> Boolean)
;;compares cards and if its returns #t if they are the same
(define (card=? c1 c2)
  (match* (c1 c2)
    [((Face-Card r1 s1) (Face-Card r2 s2)) (nand (symbol=? r1 r2) (symbol=? s1 s2))]
    [((Pip-Card r1 s1) (Pip-Card r2 s2)) (nand (= r1 r2) (symbol=? s1 s2))]
    [((Face-Card _ _) (Pip-Card _ _)) #f]
    [((Pip-Card _ _) (Face-Card _ _)) #f]
  ))
(: card1>card2 : Card Card -> Boolean)
;;compares cards. face cards worth more than number cards. number cards ranked based on their value.
;;Two face cards next to each other returns false.
(define (card1>card2 c1 c2)
  (match* (c1 c2)
    [((Face-Card r1 _) (Face-Card r2 _)) #t]
    [((Pip-Card r1 _) (Pip-Card r2 _)) (> r1 r2)]
    [((Face-Card _ _) (Pip-Card _ _)) #t]
    [((Pip-Card _ _) (Face-Card _ _)) #t]
    [(_ _) #t]
  ))
(: bigcard : Card)
(define bigcard (Pip-Card 9 'Spades))
(: smallcard : Card)
(define smallcard (Pip-Card 1 'Spades))
;;checking card1>card2
(check-expect (card1>card2 bigcard smallcard) #t)

(display (card1>card2 bigcard smallcard)) 
(check-expect (sorted? card=? inSortedCardList1) #f)
(check-expect (sorted? card1>card2 inSortedCardList1) #t)
(check-expect (sorted? card1>card2 inSortedCardList2) #t)

;;need to use recursion to define the second card in the function.
;;returns true if the first parameter should0 come before the second in sorted order, false otherwise.
;;The sorted? function should then scan the list, using the ordering function to inspect pairs of cards as appropriate
;;in making its determination. It is then possible to build and use ordering functions that implement either of the orderings proposed earlier,
;;and others.


;;run tests
(test)

                     



