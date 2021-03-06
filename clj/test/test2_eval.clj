(in-ns 'test.test2-eval)

;; Testing evaluation of arithmetic operations
(defn test []
  (pr "test2")
  (t (+ 5 (* 2 3))
     11)

  (t (- (+ 5 (* 2 3)) 3)
     8)

  (t (/ (- (+ 5 (* 2 3)) 3) 4)
     2)

  (t (/ (- (+ 515 (* 87 311)) 302) 27)
     1010)

  (t (* -3 6)
     -18)

  (t (/ (- (+ 515 (* -87 311)) 296) 27)
     -994)

;;; This should throw an error with no return value
  ;; TODO, it does but should be caught by test fn..
  ;; (t (abc 1 2 3) 2)

  ;; Testing empty list
  (t () ())

  ;; ;; Testing evaluation within collection literals
  (t [1 2 (+ 1 2)]
     [1 2 3])
 

  ;; ;; Check that evaluation hasn't broken empty collections
  (t []
     [])

  ;; TODO: Maps
  ;; (t {"a" (+ 7 8)}
  ;;    {"a" 15})

  ;; (t {:a (+ 7 8)}
  ;;    {:a 15})

  ;; (t {}
  ;;    {})

  ;; Test the test
  ;; (t 2 1)
  )
