main = do
  line <- getLine
  let n = read line :: Int
  putStrLn $ if (even 1) then "yes" else "no"
