import Text.Printf

main = do
  line <- getLine
  let arr = (map read $ words line) :: [Double]
  putStrLn . printf "%.3f" $ sum arr / 3
