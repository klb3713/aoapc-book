main = do
  line <- getLine
  let arr = map read $ words line :: [Int]
  let n = head arr
  let m = last arr
  let a = init . tail $ arr
  print $ length $ filter (<m) a
