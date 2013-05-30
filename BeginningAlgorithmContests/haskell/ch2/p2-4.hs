import Data.List
import Text.Printf

average :: [Int] -> Double
average x = realToFrac (sum x) / genericLength x

main = do
  line <- getLine
  let a = (map read $ words line) :: [Int]
  putStrLn $ printf "%d %d %.3f" (minimum a) (maximum a) (average a)
