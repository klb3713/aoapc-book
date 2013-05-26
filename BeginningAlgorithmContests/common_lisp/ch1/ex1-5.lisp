(let* ((x1 (read)) (y1 (read)) (x2 (read)) (y2 (read)))
  (format t "~,3F" (sqrt (+ (expt (- x1 x2) 2) (expt (- y1 y2) 2)))))

