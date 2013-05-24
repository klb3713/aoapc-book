import Text.Printf

main = do
  line <- getLine
  putStrLn $ printf "%.2f" $ abs (read line :: Double)

