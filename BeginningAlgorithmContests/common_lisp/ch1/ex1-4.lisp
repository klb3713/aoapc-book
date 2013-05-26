(let* ((n (read)) (rad (/ (* n pi) 180)))
  (format t "~,3F ~,3F" (sin rad) (cos rad)))
