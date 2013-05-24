import Text.Printf

solve :: Int -> Int -> String
solve n m =
  if m `mod` 2 == 1 || a < 0 || b < 0
    then "No answer"
    else printf "%d %d" a b
  where
    a = (4*n-m) `div` 2
    b = n-a

main = do
  line <- getLine
  let n:m:_ = (map read $ words line) :: [Int]
  putStrLn $ solve n m
