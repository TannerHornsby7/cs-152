#lang typed/racket

;; CMSC 15100 Winter 2022
;; Project 1
;; trace.rkt module
;; Tanner Hornsby
;;
;; Ray casting and recursive ray tracing
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
(require "camera.rkt")
(require "material.rkt")
(require "hit.rkt")
(require "object.rkt")

;;Cast Ray in World
(: cast-ray-in-world : Object -> Ray -> RGB)
;; takes an object and returns
(define (cast-ray-in-world obj)
    (local
        {(: fn : Ray -> RGB)
         (define (fn vray)
           (local
             {(define first_hit : (Option Hit) (first-entry (hit-test obj vray 0.0)))}
           (match first_hit
             ['None (ray->rgb vray)]
             [(Some H) (match ((Material-scatter (Hit-material H)) vray (Hit-pt H) (Hit-norm H))
                         [(Some (Reflect-Info r _)) r]
                         [_ (ray->rgb vray)])]
             
      ;;scatter-fun takes ray intersection_point and normal_vector and returns optional reflect info
                     )))}
      fn))

;;Trace Ray in World
(: trace-ray-in-world : Object Natural -> Ray -> RGB)
;; Given a world and a maximum tracing depth, this function returns
;; a function that will recursively trace a ray through the world
;; to compute a color
(define (trace-ray-in-world obj limit)
  (lambda ([ray : Ray])
    (local
      {(: recur_trace : Ray Natural -> RGB)
       (define (recur_trace r n)
         (if (= n 0) rgb-black
         (match (first-entry (hit-test obj r .001)) 
           ['None (ray->rgb ray)]
           [(Some hit)
            (match (get-reflection r hit)
              ['None rgb-black]
              [(Some (Reflect-Info att ref)) (rgb* att (recur_trace ref (- n 1)))])])))}
      (recur_trace ray limit)  
      )))

;;Ray Tracer
(: ray-tracer : Camera Object Natural -> Image)
;; Given a camera, world object, and max depth, render a scene
;; using the given depth limit.
(define (ray-tracer cam obj lim)
  (foreach-pixel cam
               (make-pixel-renderer
                (antialias-pixel->rgb cam
                                      (trace-ray-in-world obj lim))
                gamma-rgb->color)))

(provide
 trace-ray-in-world
 cast-ray-in-world
 ray-tracer)
