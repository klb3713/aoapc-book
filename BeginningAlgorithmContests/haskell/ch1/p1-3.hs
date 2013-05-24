main = do
  line <- getLine
  putStrLn . unwords . reverse . words $ line
