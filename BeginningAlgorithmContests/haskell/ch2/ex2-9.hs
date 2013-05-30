import Text.Printf

solve :: Int -> Int -> Int -> [Int]
solve _ _ 0 = []
solve a b c =
  q : (solve (a2 `mod` b) b (c-1)) where
    a2 = a * 10
    q = a2 `div` b + (if c == 1 && (a2 `mod` b) * 10 `div` b >= 5 then 1 else 0)

printDigits :: [Int] -> IO ()
printDigits [] = return ()
printDigits (x:xs) = do
  putStr $ printf "%d" x
  printDigits xs

main = do
  line <- getLine
  let a:b:c:_ = (map read $ words line) :: [Int]
  putStr $ printf "%d." (a `div` b)
  printDigits $ solve (a `mod` b) b c
