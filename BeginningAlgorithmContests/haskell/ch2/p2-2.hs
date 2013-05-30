cycleLen :: Int -> Int
cycleLen 1 = 0
cycleLen n
  | n `mod` 2 == 1 = (cycleLen $ n*3+1) + 1
  | otherwise      = (cycleLen $ n `div` 2) + 1

main = do
  line <- getLine
  let n = read line :: Int
  print . cycleLen $ n

