main = do
  print $ filter issqrt [a*1100+b*11 | a <- [1..9], b <- [0..9]] where
    isqrt = round . sqrt . fromIntegral
    issqrt x = (isqrt x) * (isqrt x) == x
