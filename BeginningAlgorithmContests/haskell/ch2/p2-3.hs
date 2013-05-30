factorial :: Integer -> Integer
factorial n = foldl1 (*) [1..n]

main = do
  line <- getLine
  let n = read line :: Integer
  print . (`mod` 10^6) . sum . map factorial $ [1..n]
