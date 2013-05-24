import Data.List

main = do
  line <- getLine
  let a = (sort . map read $ words line) :: [Int]
  putStrLn . unwords $ map show a
