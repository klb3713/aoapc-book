import Control.Monad

main = do
  line <- getLine
  let n = read line :: Int
  forM_ [0..n-1] (\i -> do
    putStr $ take i (repeat ' ')
    putStrLn $ take (2*(n-i)-1) (repeat '*'))
