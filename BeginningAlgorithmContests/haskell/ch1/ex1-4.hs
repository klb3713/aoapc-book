import Text.Printf

main = do
  line <- getLine
  let n = read line :: Double
      rad = n / 180.0 * pi
  putStrLn $ printf "%.3f %.3f" (sin rad) (cos rad)
