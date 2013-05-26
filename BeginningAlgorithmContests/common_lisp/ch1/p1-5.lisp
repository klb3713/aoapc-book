(let* ((a (read)) (b (read)) (c (read)) (lst (sort (list a b c) #'<)))
  (format t "~D ~D ~D" (car lst) (second lst) (third lst)))
