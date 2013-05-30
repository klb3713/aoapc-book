import Text.Printf

main = do
  let terms = [(-1)^i * (1.0 / realToFrac (i*2+1)) | i <- [0..]]
  let needed = takeWhile (\x -> abs x > 1e-6) terms
  putStrLn $ printf "%.6f" (sum needed :: Double)
