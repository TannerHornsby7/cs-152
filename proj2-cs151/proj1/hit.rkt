#lang typed/racket

;; CMSC 15100 Winter 2022
;; Project 1
;; hit.rkt module
;; Tanner Hornsby
;;
;; This module contains the definition of the Hit and Hit-List types
;;

;; load custom definitions
;;
(require "../include/cs151-core.rkt")

;; load image library definitions
;;
(require "../include/cs151-image.rkt")

;; load testing infrastructure
;;
(require typed/test-engine/racket-tests)

;; project modules
;;
(require "util.rkt")
(require "math-util.rkt")
(require "color.rkt")
(require "material.rkt")

;; The Parity of a ray's intersection with an object is either `IN for a
;; ray entering an object, or `OUT for a ray leaving an object.
(define-type Parity (U 'IN 'OUT))

;; A (Hit ...) records an intersection (aka "hit") between a Ray R
;; and an object.
(define-struct Hit
  ([parity : Parity]        ;; specifies if the hit is an entry or exit
   [t : Float]              ;; value of t such that R(t) is the point
                            ;; where the ray R intersects the object
   [pt : Float3]            ;; The point of intersection (i.e., R(t))
   [norm : Float3]          ;; Unit-length normal vector at pt
   [material : Material]))  ;; The material of the object at pt

;;Defining Test Hit's and Hit Lists
(define TH1 (Hit 'IN 1.0 (Float3 1.0 1.0 1.0) (Float3 1.0 1.0 1.0) flat-black))
(define TH2 (Hit 'OUT 1.5  (Float3 1.0 2.0 1.0) (Float3 1.0 2.0 1.0) flat-black))
(define TestHitList1 (list TH1 TH2))
(define TestHitList2 (list))

;; entry? : Hit -> Boolean
(: entry? : Hit -> Boolean)
;;determines if a given Hit is an entry, if it is returns true
(define (entry? hit)
(symbol=? (Hit-parity hit) 'IN))
;;testing
(check-expect (entry? TH1) #t)
(check-expect (entry? TH2) #f)

(: hit< : Hit Hit -> Boolean)
;;The hit< function compares the t values of two hits and returns true if the first hit is closer (i.e., has a smaller t
;;value) than the second.You can use the flat-black material to construct hits for testing these functions.
(define (hit< h1 h2)
(< (Hit-t h1) (Hit-t h2)))
;;testing
(check-expect (hit< TH1 TH2) #t)
;;(map hit->info

;;get reflection
(: get-reflection : Ray Hit -> (Option Reflect-Info))
;; given a ray and an entry hit record for it, get the optional reflection
;; info for the hit record's material.   Return 'None for exit hits.
(define (get-reflection vray vhit)
  (match vhit
    [(Hit 'IN t pt n mat) ((Material-scatter (Hit-material vhit)) vray pt n)]
    [_ 'None]))

;; a Hit-List is a list of Hit records sorted by increasing t value that
;; describes how a ray interacts with an object.  We require that the parities
;; of adjacent hits be opposite.  In other words, a ray cannot leave (resp. enter)
;; the object unless it is inside (resp. outside) the object.
;;
(define-type Hit-List (Listof Hit))

;; We use the empty list to represent a miss
;;
(define miss : Hit-List '())

;;first entry function
(: first-entry : Hit-List -> (Option Hit))
;;takes a valid hit list and returns some hit where hit is the first entry on the list
;;otherwisee returns 'None
(define (first-entry hl)
  (match hl
    [(cons x xr) (if (entry? x) (Some x) 'None)]
    [_ 'None]))
;; testing first-entry
(check-expect (first-entry TestHitList1) (Some TH1))
(check-expect (first-entry TestHitList2) 'None)

;; ==== Testing support ====

(: valid-hit-list? : Hit-List -> Boolean)
;; test that a hit list is valid.  I.e., that its t values are increasing and
;; that parities alternate.  This function can be used to check the correctness
;; of other functions, but otherwise does no useful work.
(define (valid-hit-list? hits)
  (local
    {(: checker : Parity Real Hit-List -> Boolean)
     ;; check the hits, where p1 is the parity and t1 is the t value of the
     ;; preceeding hit
     (define (checker p1 t1 hits)
       (match hits
         [(cons (Hit p2 t2 _ _ _) hitr)
          (and (<= t1 t2) (not (symbol=? p1 p2)) (checker p2 t2 hitr))]
         ['() #t]))}
    (match hits
      [(cons (Hit p t _ _ _) hitr) (checker p t hitr)]
      ['() #t])))

;; A (Hit-Info ...) struct records the geometric information about a
;; hit record.  This structure can be used to implement check-within
;; tests, since it does not involve materials, which cannot be compared.
(define-struct Hit-Info
  ([parity : Parity]        ;; specifies if the hit is an entry or exit
   [t : Float]              ;; value of t such that R(t) is the point
                            ;; where the ray R intersects the object
   [pt : Float3]            ;; The point of intersection (i.e., R(t))
   [norm : Float3]))        ;; Unit-length normal vector at pt

(: hit->info : Hit -> Hit-Info)
;; extract the hit-info from a Hit record
(define (hit->info hit)
  (match hit
    [(Hit p t pt n _) (Hit-Info p t pt n)]))

;;Further checking first entry using hit->info
;;(display (map hit->info TestHitList1))
(test)

;;;;;;;;;;
;; Exports
;;;;;;;;;;

(provide Parity
         (struct-out Hit)
         first-entry 
         get-reflection
         Hit-List
         miss
         hit<
         (struct-out Hit-Info))
