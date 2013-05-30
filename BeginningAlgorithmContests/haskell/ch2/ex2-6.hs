import Text.Printf

main = do
  line <- getLine
  let n = read line :: Int
  let ans = sum [1.0 / (realToFrac x) | x <- [1..n]] :: Double
  putStrLn $ printf "%.3f" $ ans
