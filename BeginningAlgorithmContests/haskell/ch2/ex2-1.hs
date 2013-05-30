import qualified Data.Text as T

main = do
  line <- getLine
  let n = T.strip . T.pack $ line
  print $ T.length n
