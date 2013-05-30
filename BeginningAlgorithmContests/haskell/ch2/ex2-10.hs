import Control.Monad
import Text.Printf
import Data.List

isSolution :: Int -> Bool
isSolution x = (sort big) == "123456789" where
  big = (show x) ++ (show $ x*2) ++ (show $ x*3)

main = do
  forM_ (filter isSolution [123..329]) (\i -> do
    putStrLn $ printf "%d %d %d" i (i*2) (i*3))
