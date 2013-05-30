import Text.Printf

main = do
  line <- getLine
  let n:m:_ = (map read $ words line) :: [Integer]
  let ans = sum [1.0 / realToFrac(i^2) | i <- [n..m]] :: Double
  putStrLn $ printf "%.5f" ans

