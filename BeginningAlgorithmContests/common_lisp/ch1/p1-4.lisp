(defun solve (n m)
  (let* ((a (/ (- (* n 4) m) 2)) (b (- n a)))
    (if (or (oddp m) (< a 0) (< b 0))
        "No answer"
        (format nil "~A ~A" a b))))

(let ((n (read)) (m (read)))
  (format t "~A" (solve n m)))
