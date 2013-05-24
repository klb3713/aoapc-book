main = do
  line <- getLine
  let n = read line :: Int
  print $ n*(n+1) `div` 2
