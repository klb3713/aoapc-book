solve :: Int -> Int -> Int -> String
solve a b c =
  let s = filter (\x -> x `mod` 3 == a && x `mod` 5 == b && x `mod` 7 == c) [10..100] in
  case s of
    []  -> "No Answer"
    x:_ -> show (head s)

main = do
  line <- getLine
  let a:b:c:_ = (map read $ words line) :: [Int]
  putStrLn $ solve a b c

