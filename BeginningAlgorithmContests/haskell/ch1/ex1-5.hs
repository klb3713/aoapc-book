import Text.Printf

main = do
  line <- getLine
  let x1:y1:x2:y2:_ = (map read $ words line) :: [Double]
  putStrLn $ printf "%.3f" $ sqrt $ (x1-x2)^2+(y1-y2)^2
