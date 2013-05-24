import Text.Printf

main = do
  line <- getLine
  let money = (read line :: Double) * 95.0
  putStrLn $ printf "%.2f" $ if money < 300 then money else money * 0.85
