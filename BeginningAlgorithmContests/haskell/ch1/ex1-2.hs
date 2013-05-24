import Text.Printf

main = do
  line <- getLine
  let f = read line :: Double
  putStrLn . printf "%.3f" $ 5*(f-32)/9
