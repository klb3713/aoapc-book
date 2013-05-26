(let* ((n (read)) (money (* 95 n)))
  (format t "~,3F" (if (>= money 300) (* 0.85 money) money)))
