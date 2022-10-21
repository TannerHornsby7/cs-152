#lang typed/racket

;; CMSC 15100 Winter 2022
;; Project 1
;; camera.rkt module
;; Tanner Hornsby
;;
;; This module implements the Camera abstraction
;;

;; load custom definitions
;;
(require "../include/cs151-core.rkt")

;; include testing framework
(require typed/test-engine/racket-tests)

;; load image library definitions
;;
(require "../include/cs151-image.rkt")

;; project modules
;;
(require "math-util.rkt")
(require "color.rkt")
;;(require "object.rkt")
;;for testing

;; the representation of a Camera for the ray tracer.  The camera
;; is assumed to be at the origin looking down the -Z axis.
(define-struct Camera
  [(wid : Natural)           ;; width of image
   (ht : Natural)            ;; height of image
   (n-samples : Natural)     ;; number of samples per pixel
   (focal-len : Float)])     ;; distance to image plane (in -Z direction)

;; A Pixel-Renderer is a function that takes the row and column of a pixel
;; and produces a Racket Image-Library Color
(define-type Pixel-Renderer (Natural Natural -> Color))

(: make-pixel-renderer : (Natural Natural -> RGB) (RGB -> Color) -> Pixel-Renderer)
;; compose a function that maps pixel coordinates to RGB values with
;; an RGB to Image-Library Color converter
(define (make-pixel-renderer pixel->rgb rgb->color)
  (lambda ([row : Natural] [col : Natural]) (rgb->color (pixel->rgb row col))))

;;list of pixels to Image function
;;going to use color-list->bitmap(Listof Color Natural Natural->Image) on the accumulated Color lists
;;after the double recursive is called.

;;making a test cam(define rx : Float (/ 1.0 (random)))
;;cam400x200x1-0.0
(define cam (Camera 400 200 1 0.0))
;;building for each pixel
(: foreach-pixel : Camera Pixel-Renderer -> Image)
;;The outer loop will iterate over the rows of
;;the image starting from the bottom an(define sphere-1 (make-sphere (Float3 0.0 0.0 -2.0) 0.5 normal-material))d the inner
;;loop will iterate over the columns of a row going
;;from right-to-left. An accumulator will be use to build the list of pixels.
(define (foreach-pixel var_cam var_pix)
  (if (and (> (Camera-wid var_cam) 0) (> (Camera-ht var_cam) 0))
      (local
        {(: up-row : Natural (Listof Color) -> (Listof Color))
         ;;function for iterating up the rows of the Image
         (define (up-row r Lr)
           (if (= r (Camera-ht var_cam)) Lr (up-row (+ r 1) (append Lr (across-col (- (Camera-wid var_cam) 1) r '())))))
     
         (: across-col : Natural Natural (Listof Color) -> (Listof Color))
         ;;funct for iterating across the columns of the Image
         (define (across-col cc rc Lc)
           (if (= cc 0) (cons (var_pix rc cc) Lc) (across-col (- cc 1) rc (cons (var_pix rc cc) Lc))))} 
        (color-list->bitmap (up-row 0 '()) (Camera-wid var_cam) (Camera-ht var_cam)))
      (error "invalid height/width")))

(local
  {(define wid : Natural 400)
   (define ht : Natural 200)}
  (foreach-pixel
   cam
   (make-pixel-renderer
    (lambda ([r : Natural] [c : Natural])
      (if (and (< r ht) (< c wid))
          (RGB (/ (->fl c) (->fl wid))
               (/ (->fl (- ht r)) (->fl ht))
               0.2)
      (error "row/column out of range")))
   rgb->color)))

;; Ray for Pixel Function
(: ray-for-pixel : Camera -> (Natural Natural -> Ray))
;;Takes in a Camera and returns a function for generating a ray for a pixel specified by its row and column
;;pw= 2/w
;;pw/2 - 1 = center of pixel laterally
;;(cam height/ cam width) - (pixel width/2) = center of pixel horizontally.
(define (ray-for-pixel var_cam)
  (lambda ([c : Natural] [r : Natural])
    (local
      {;;pw = pixel_width = 2/w
       (define pw : Float (/ 2.0 (->fl (Camera-wid var_cam))))
       ;;ph = pixel height = 2*h/w
       (define ph : Float (* 2.0 (/ (->fl (Camera-ht var_cam)) (->fl (Camera-wid var_cam)))))
       ;;define x0
       (: x0 Float)
       (define x0 (- (/ pw 2.0) 1.0))
       ;;define y0
       (: y0 Float)
       (define y0  (- (/ ph 2.0) (/ pw 2.0)))
       ;;given a pixel, calculate its center and returns its float3 location
       (: pixel_center Float3)
       (define pixel_center
         (Float3        (+ x0 (* (->fl c) pw))
                        (- y0 (* (->fl r) pw))
                 (- (Camera-focal-len var_cam))))}
    (make-ray fl3-zero
         pixel_center))))
;;check that the last element of the array is properly converted to a Ray
;;(check-within ((ray-for-pixel cam) 0 0) (Ray (Float3 0.0 0.0 0.0)
             ;; (Float3 (+ (/ 399.0 400.0) 2) (- (- (/ 1.0 400) .5) 1) (-(Camera-focal-len cam)))) .05)
;; Rays for Pixel Function
(: rays-for-pixel : Camera -> (Natural Natural -> (Listof Ray)))
;;Rays for pixel takes in a camera and outputs a function for finding the list of rays at pixel(c, r)
(define (rays-for-pixel cam)
  (lambda ([c : Natural] [r : Natural])
    (local
      {;;pw = pixel_width = 2/w
       (define pw : Float (/ 2.0 (->fl (Camera-wid cam))))
       (: comp-ray-list : Natural (Listof Ray) -> (Listof Ray))
       (define (comp-ray-list n prod)
         (local
           {(define rx : Float (random))
            (define ry : Float (random))
            (define ray_dir : Float3
              (Float3
               (- (* pw (+ c rx)) 1.0)
               (- (/ (->fl (Camera-ht cam)) (->fl (Camera-wid cam)))
                  (* pw (+ r ry)))
               (- (Camera-focal-len cam))))}
         (if (< n (Camera-n-samples cam))
             (comp-ray-list (+ n 1) (cons (make-ray fl3-zero ray_dir) prod))
             prod)))}
      (comp-ray-list 0 '()))))

;;(test)

;;pixel to rgb
(: pixel->rgb : Camera (Ray -> RGB) -> Natural Natural -> RGB)
;; given a camera and a ray-tracing function, return a function that
;; traces the ray for the given pixel
(define (pixel->rgb var_cam2 ray_trace)
    (local
      {(: ray_funct : Natural Natural -> Ray)
       (define ray_funct (ray-for-pixel var_cam2))
       }
      
      (lambda ([c : Natural] [r : Natural]) (ray_trace (ray_funct r c)))))

;;Anti alias pixel to rgb
(: antialias-pixel->rgb : Camera (Ray -> RGB) -> Natural Natural -> RGB)
;; given a camera and a ray-tracing function, return a function that
;; traces a list of rays for the given pixel and returns their average
(define (antialias-pixel->rgb cam ray_trace)
   (local
      {(define scale_factor : Float (if (= (->fl (Camera-n-samples cam)) 0.0) 1.0 (/ 1.0 (->fl (Camera-n-samples cam)))))
       (: ray_funct : Natural Natural -> (Listof Ray))
       (define ray_funct (rays-for-pixel cam))}
      (lambda ([c : Natural] [r : Natural]) (rgb-scale scale_factor
      (foldl (lambda ([ray : Ray] [rgb : RGB]) (rgb+ (ray_trace ray) rgb)) (RGB 0.0 0.0 0.0) (ray_funct r c))))))

  

;;;;; TESTING


(: ray->rgb : Ray -> RGB)
;; a function for testing ray generation.  It maps a ray to a color in
;; the white-to-blue range based on the Y component of the ray's direction
;; vector.
(define (ray->rgb ray)
  (match ray
    [(Ray _ dir)
     (local
       {(define t : Float (* 0.5 (+ 1.0 (Float3-y dir))))}
       (rgb-lerp rgb-white t (RGB 0.5 0.7 1.0)))]))

;;;;;;;;;;
;; Exports
;;;;;;;;;;

(provide (struct-out Camera))

(provide foreach-pixel
         make-pixel-renderer
         pixel->rgb
         ray->rgb
         antialias-pixel->rgb)
