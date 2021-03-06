(in-ns 'test.test8-macros)
;; Testing trivial macros
(defmacro one [] 1)
(t (one)
   1)
(defmacro two [] 2)
(t (two)
   2)

;; Testing unless macros
(defmacro unless [pred a b] `(if ~pred ~b ~a))
(t (unless false 7 8)
   7)
(t (unless true 7 8)
   8)
(defmacro unless2 [pred a b] (list 'if (list 'not pred) a b))
(t (unless2 false 7 8)
   7)
(t (unless2 true 7 8)
   8)

;; ;; Testing macroexpand
(t (macroexpand '(unless2 2 3 4))
   (if (not 2) 3 4))

;; ;; Testing evaluation of macro result
(defmacro identity [x] x)
(t (let [a 123] (identity a))
   123)

;; ;; Test that macros do not break empty list
(t ()
   ())


;; ;; Testing non-macro function
(t (not (= 1 1))
   false)
(t (not (= 1 1))
   false)
;;; This should fail if it is a macro
(t (not (= 1 2))
   true)
(t (not (= 1 2))
   true)

;; ;; Testing nth, first and rest functions

(t (nth (list 1) 0)
   1)
(t (nth (list 1 2) 1)
   2)
(t (nth (list 1 2 nil) 2)
   nil)
(def x "x")
;; (def x (nth (list 1 2) 2))
(t x
   "x")

(t (first (list))
   nil)
(t (first (list 6))
   6)
(t (first (list 7 8 9))
   7)

(t (rest (list))
   ())
(t (rest (list 6))
   ())
(t (rest (list 7 8 9))
   (8 9))

;; ;; Testing cond macro

(t (cond)
   nil)
(t (cond true 7)
   7)
(t (cond true 7 true 8)
   7)
(t (cond false 7 true 8)
   8)
(t (cond false 7 false 8 "else" 9)
   9)
(t (cond false 7 (= 2 2) 8 "else" 9)
   8)
(t (cond false 7 false 8 false 9)
   nil)

(t (cond false 7 false 8 false 9)
   nil)

;; ;; Testing EVAL in let

(t (let [x (cond false "no" true "yes")] x)
   "yes")


;; ;; Testing nth, first, rest with vectors

(t (nth [1] 0)
   1)
(t (nth [1 2] 1)
   2)
(t (nth [1 2 nil] 2)
   nil)
;; (def x "x")
;; (def x (nth [1 2] 2))
;; x
;; ;=>"x"

(t (first [])
   nil)
(t (first nil)
   nil)

(t (first [10])
   10)
(t (first [10 11 12])
   10)
(t (rest [])
   ())
(t (rest ())
   ())
(t (rest [10])
   ())
(t (rest [10 11 12])
   (11 12))
(t (rest (cons 10 [11 12]))
   (11 12))

;; ;; Testing EVAL in vector let

(t (let [x (cond false "no" true "yes")] x)
   "yes")

(def x2 2)
(defmacro a [] x2)
(t (a)
   2)

(t (let [x2 3] (a))
   2)
