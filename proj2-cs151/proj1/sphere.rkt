#lang typed/racket

;; CMSC 15100 Winter 2022
;; Project 1
;; sphere.rkt module
;; Tanner Hornsby
;;
;; This module contains the implementation of the sphere object
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
(require "material.rkt")
(require "hit.rkt")
(require "object.rkt")
;;added for testing
(require "color.rkt")
(require "camera.rkt")
(require "trace.rkt")
;;(require "examples.rkt")

(: make-sphere : Float3 Float Material -> Object)
;; make a sphere object with the given center, radius, and material
(define (make-sphere center radius material)
  (Object (lambda ([ray : Ray] [min-t : Float])
               ;;vector from the center of the sphere to the ray's origin
               (define V : Float3 (fl3- (Ray-origin ray) center))
               ;;defining the quadratic with the coefficients below
               ;;a
               (define a : Float 1.0)
               ;;b
               (define b : Float (* 2.0 (fl3-dot (Ray-dir ray) V)))
               ;;c
               (define c : Float (- (fl3-dot V V) (* radius radius)))
               ;;d (determinant)
               (define d : Float (- (* b b) (* 4 a c)))
               ;;Surface Normal
               (: Sn : Float -> Float3)
               (define (Sn vt) (fl3-scale (/ 1.0  radius) (fl3- (ray-point-at ray vt) center)))
               ;;point of intersection is given by the below quadratic
                 
               (cond
                   [(<= d 0) miss]
                   [else
                    (local
                      {(define t1 : Float (/ (* (+ b (sqrt d)) -1) 2))
                       (define t2 : Float (/ (- (sqrt d) b) 2))}
                      (cond
                        [(< t2 min-t) miss]
                        [(and (< t1 min-t) (< min-t t2)) (cons (Hit 'OUT t2 (ray-point-at ray t2) (Sn t2) material) '())]
                        [else (cons (Hit 'IN t1 (ray-point-at ray t1) (Sn t1) material)
                                                    (cons (Hit 'OUT t2 (ray-point-at ray t2) (Sn t2) material) '()))]))]))))
;;Testing make-sphere
(define some-test-ray : Ray (Ray fl3-zero (Float3 5.0 5.0 5.0)))
;;inside the sphere
(hit-test (make-sphere fl3-zero 1.0 (flat-material (RGB 1.0 0.0 0.0))) some-test-ray 0.0)
(hit-test (make-sphere (Float3 5.0 5.0 5.0) 1.0 (flat-material (RGB 1.0 0.0 0.0))) some-test-ray 0.0)


"== eyeball test for ray cast: flat material"
(define sphere-0
  (make-sphere (Float3 0.0 0.0 -2.0) 0.5 (flat-material (RGB 1.0 0.0 0.0))))

(define cam-400x200x1 (Camera 400 200 1 1.0))

(foreach-pixel cam-400x200x1
               (make-pixel-renderer
                (pixel->rgb cam-400x200x1 (cast-ray-in-world sphere-0))
                rgb->color))

(define sphere-1 (make-sphere (Float3 0.0 0.0 -2.0) 0.5 normal-material))
"== eyeball test for ray cast: normal material"
(time (foreach-pixel cam-400x200x1
                     (make-pixel-renderer
                      (pixel->rgb cam-400x200x1 (cast-ray-in-world sphere-1))
                      rgb->color)))

"== eyeball test for ray cast: normal material and two spheres"
(define sphere-2 (make-sphere (Float3 0.0 -100.5 -2.0) 100.0 normal-material))
(define world-1 (list->object (list sphere-1 sphere-2)))

(foreach-pixel cam-400x200x1
               (make-pixel-renderer
                (pixel->rgb cam-400x200x1 (cast-ray-in-world world-1))
                rgb->color))

;;;;;;;;;;
;; Exports
;;;;;;;;;;

(provide make-sphere)
