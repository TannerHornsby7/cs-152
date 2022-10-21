#lang typed/racket
(require typed/test-engine/racket-tests)
(require "../include/cs151-core.rkt")

(: leap? : Integer -> Boolean)
(define (leap? year)
  (cond [(= (remainder year 400) 0) #t]
        [(and (= (remainder year  100) 0) (not (= (remainder year 400) 0))) #f]
        [else (if (= (remainder year 4) 0) #t #f)]))
;;Return true if and only if the given year is a leap year. The rules for a leap year are sometimes oversimplified. Here is the full definition:
;;A year is a leap year if it is divisible by 400.
;;A year is not a leap year if it is divisible by 100 and not divisible by 400.
;;A year not covered by the above rules is a leap year if it is divisible by 4.
;;Although much of this assignment relies on the constraint that years be between 1900 and 2099, do not constrain this particular function.
;;To make sure the leap year function works properly, I will chose years: 2000(true),1900(false), 2012(true),and 3000(true).
;;I chose these values specifically to test that the function works for each condition, and the function works for years outside of the constraint(1900-2099)
(check-expect (leap? 2000) #t)
(check-expect (leap? 1900) #f)
(check-expect (leap? 1999) #f)
(check-expect (leap? 2012) #t)
(check-expect (leap? 3000) #f)
(check-expect (leap? 12) #t)

;;first-day takes month and year and determines the first day of the month 0-6. It uses helper function month-adjustment to do this.
(: first-day : Integer Integer -> Integer)
(define (first-day m y)
  (exact-ceiling(remainder (+ (- y 1900) (month-adjustment m y) 1 (quotient y 4)) 7))
  )
(check-expect  (first-day 1 2022) 6)
(check-expect  (first-day 1 2022) 6)
(check-expect  (first-day 1 2022) 6)

;;month-adjustment helper function
;;takes month and year and determines the month adjustment to be used within first-day calculation.
(: month-adjustment : Integer Integer -> Integer)
  (define (month-adjustment m y)
    (cond [(= m 1) (if (leap? y) 0 1)]
          [(= m 2) (if (leap? y) 3 4)]
          [(= m 3) 4]
          [(= m 4) 0]
          [(= m 5) 2]
          [(= m 6) 5]
          [(= m 7) 0]
          [(= m 8) 3]
          [(= m 9) 6]
          [(= m 10) 1]
          [(= m 11) 4]
          [(= m 12) 6]
          [else
           (error "invalid input, enter a month value between 1-12 and a year between 1900 and 2099")
           ])
  )
;;Given a month and year, return a value between 0 and 6, as described earlier, for the day of the week on which the first of the month falls.
;;testing month-adjustment
(check-expect (month-adjustment 1 2000) 0)
(check-expect (month-adjustment 2 1999) 4)
(check-expect (month-adjustment 12 1999) 6)

;;row function produces one of the lines in the calendar display, start indicates the first day of the week, end indicates the last day of the month.
(: row : Integer Integer -> String)
(define (row start last)
  (row-aux start last start (number->string start)))

;;function to create the first week of the month's row.
(: first-week-row : Integer Integer Integer -> String)
(define (first-week-row last m y)
(row-aux (- 1 (first-day m y)) last (- 1 (first-day m y)) "" ))

 ;;row auxilliary funciton
(: row-aux : Integer Integer Integer String -> String)
(define (row-aux start last i prod)
(if (and (> i 0) (< i (+ start 7)) (<= i last)) (row-aux start last (+ i 1) (string-append prod (number->string (+ i 1)) " "))
    (row-aux start last (+ i 1) (string-append prod "   "))))
;;this tail recursive function outputs creates a row of dates for the calendar given the start date and end of the month.
;; the biggest Issue I could see with this code would be if the start date is not the beginning of the week. In that case
;; we would need to end it when the dates reach saturday.
;;(display (row-aux 1 30 1 (number->string 1)))

;;(display (first-week-row 30 1 2022))
;;(display "hello")

;;calendar function uses the previous functions described to create a string of a calendar month based on the month and year inputed
;;Given a month and year (between 1900 and 2099, inclusive), this should produce a string formatted like the earlier example output.

(: calendar : Integer Integer -> String)
(define (calendar m y)
  (define s (string-append (cond [(= m 1) "January"]
          [(= m 2) "February"]
          [(= m 3) "March"]
          [(= m 4) "April"]
          [(= m 5) "May"]
          [(= m 6) "June"]
          [(= m 7) "July"]
          [(= m 8) "August"]
          [(= m 9) "September"]
          [(= m 10) "October"]
          [(= m 11) "November"]
          [(= m 12) "December"]
          [else
           (error "invalid input, enter a month value between 1-12 and a year between 1990-2099")
           ]) " " (number->string y) "\n" "Su Mo Tu We Th Fr Sa" "\n" (first-week-row  31 m y) "\n"(row (+ (- 1 (first-day m y)) 7) 31))
  )
s
  )
(display (calendar 1 2022))
(display (first-week-row 30 1 2022))
(display (first-day 1 2022))
(display "hello")





(test)