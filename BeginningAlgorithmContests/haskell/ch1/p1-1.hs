import Text.Printf

main = do
  line <- getLine
  let r:h:_ = (map read $ words line) :: [Double]
  putStrLn . printf "Area = %.3f" $ pi*r*r*2+2*pi*r*h
