#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

;;Temporary Definitions for Error Testing
;;(: deducted-income : Integer Integer Integer Boolean -> Integer)
;; deducted-income: Determine the income after deducing either standard or itemized
;; parameter "income": yearly income in thunks
;; parameter "itemize": itemized deduction based on gallons-per-year, trips, and num-people
;; parameter "standard": standard deduction based on family unit and income
;; parameter "should itemize?": boolean expression of whether to use itemized or standard deduction
;; parameter "withheld": amount of thunks already withheld
;; output: integer income after deductions
;;(define (deducted-income income (itemized income num-people trips gallons-per-year) (standard num-people) (should-itemize? income num-people trips gallons-per-year))
;;(if (should-itemize? income num-people trips gallons-per-year) (-= income (itemized income num-people trips gallons-per-year)))
;;(else (-= income (standard num-people))))
 
(: marginal-tax : Integer -> Integer)
;; marginal-tax: compute the amount of tax owed on the given income.
;; parameter "post-deductions-income" uses post-deductions-income with the tax bracket calculation to determine the marginal tax
;; output: the amount of marginal tax owed
(define (marginal-tax deducted-income)
  ;;the code below brackets the tax of income for each specified level, using exact-ceiling to round each product up to the nearest int
  ;;
  (cond [(> 32000 deducted-income 18000) (exact-ceiling(* .15 (- deducted-income 18000)))]
  [(> 56000 deducted-income 32000) (exact-ceiling(+ (* .15 14000) (* .25 (- deducted-income 32000))))]
  [(> deducted-income 56000) (exact-ceiling(+ (* .15 14000) (* .25 18000) (* .35 (- deducted-income 56000))))]
  [else 0])
)
(check-expect (marginal-tax 15000) 0)
(check-expect (marginal-tax 30000) 1800)
(check-expect (marginal-tax 50000) 6600)
;;testing the marginal-tax function with numbers in each bracket to ensure the
;;summation and percentages of each works properly



(: transit-deduction : Integer Integer -> Integer)
;; transit-deduction: compute deduction of 10 thunks per
;;  trip, but not more than 25% of income
;; parameter "income": an integer number of thunks
;; parameter "trips": the number of trips on transit
;; output: deduction as described above
(define (transit-deduction income trips)
  (cond [(<= (* 10 trips) (exact-ceiling(* .25 income))) (* 10 trips)]
  [else (exact-ceiling(* .25 income))])
)
;;The function above multiplies trips by 10 and compares this with the up-rounded version of 25% of the income
;; if 10 * trips is larger than 25% of the income, then we will use 25% of the income for the deduction
;;otherwise, we will use 10 * trips for our deduction

(check-expect (transit-deduction 100 1) 10)
(check-expect (transit-deduction 100 3) 25)
;;these checks verify that both conditions of the if statement work properly



(: hummingbird-deduction : Integer Integer -> Integer)
;; hummingbird-deduction: compute deduction of gallons-per-year-per-person
;;  in thunks times eight, but not more than 4000
;; parameter "gallons-per-year": the nectar provided in gallons per year
;; parameter "num-people": the number of people in the family unit
;; output: deduction as described above
(define (hummingbird-deduction gallons-per-year num-people)
  (cond [(< (exact-ceiling(* 8 (/ gallons-per-year num-people))) 4000) (exact-ceiling(* 8 (/ gallons-per-year num-people)))]
      [else 4000]))
;; the hummingbird deduction function described above checks whether the rounded up version of 8 * gallons/people is smaller than 4000
;; if it is lower than 4000 then we use 8 * gallons/people
;; otherwise we use 4000
(check-expect (hummingbird-deduction 1000 1) 4000)
(check-expect (hummingbird-deduction 100 1) 800)
;; the check-expect above makes sure that both conditions of the if statement execute properly.

(: itemized : Integer Integer Integer Integer -> Integer)
;; itemized: compute itemized deduction on income
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "trips": the number of trips on transit
;; parameter "gallons-per-year": the nectar provided in gallons per year
;; output: total itemized deduction for this family unit
(define (itemized income num-people trips gallons-per-year)
  (+ (hummingbird-deduction gallons-per-year num-people) (transit-deduction income trips)))
;;the itemized deduction is just the sum of both hummingbird and transit deductions.
(check-expect (itemized 100 1 0 0) 0)
;; this check expect verifies that the sum of hummingbird and transit is correct

(: standard : Integer -> Integer)
;; standard: compute the standard deduction for a family unit,
;;  which is just 2000 thunks per person
;; parameter "num-people"
;; output: the deduction for that number of people
(define (standard num-people) (* 2000 num-people))
;;the standard deduction is defined as 2000 times the number of people in the family unit. this is shown in the code above.

(: should-itemize? : Integer Integer Integer Integer -> Boolean)
;; should-itemize?: should family unit itemize or take standard? 
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "trips": the number of trips on transit
;; parameter "gallons-per-year": the nectar provided in gallons per year
;; output: #t if itemized deduction is larger than standard, #f otherwise
(define (should-itemize? income num-people trips gallons-per-year)
  (> (itemized income num-people trips gallons-per-year) (standard num-people))
  )
(check-expect (should-itemize? 100 1 0 0) #f)
;;if the family didn't do any of the itemized deductables then they shouldn't itemize

(: tax-return : Integer Integer Integer Integer Integer -> Integer)
;; tax-return: Determine the negative (refund) or positive (payment) due
;;  family unit, given their income as well as the amount withheld.
;; parameter "income": yearly income in thunks
;; parameter "num-people": number of people in family unit
;; parameter "trips": the number of trips on transit
;; parameter "gallons-per-year": the nectar provided in gallons per year
;; parameter "withheld": amount of thunks already withheld
;; output: positive or negative debt to the TRS (negative debt is a refund)
(define (tax-return income num-people trips gallons-per-year withheld)
     (cond
       [(should-itemize? income num-people trips gallons-per-year) (- (marginal-tax(- income (itemized income num-people trips gallons-per-year))) withheld)]
     [else (- (marginal-tax(- income (standard num-people))) withheld)])
)
(check-expect (tax-return 100 1 0 0 0) 0)
  ;;Recall that((marginal-tax income) - withheld). The function above uses should-itemize? to determine the deductions which will be performed on the
  ;;Income and then uses that income in the marginal-tax calculation. Then, it subtracts marginal-tax from withheld to give the specified tax return.
(test)