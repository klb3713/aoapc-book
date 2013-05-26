(defun solve (a b c)
  (let* ((lst (sort (list a b c) #'<)) (a2 (first lst)) (b2 (second lst)) (c2 (third lst)))
    (cond ((= (+ (* a2 a2) (* b2 b2)) (* c2 c2)) "yes")
          ((<= (+ a2 b2) c2) "not a triangle")
          (t "no"))))

(let ((a (read)) (b (read)) (c (read)))
  (format t "~A" (solve a b c)))
