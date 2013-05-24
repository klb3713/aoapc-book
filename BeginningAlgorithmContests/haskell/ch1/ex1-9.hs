main = do
  line <- getLine
  let a:b:c:_ = (map read $ words line) :: [Int]
  putStrLn $ solve a b c where
    solve a b c
      | a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a = "yes"
      | a+b<=c || a+c<=b || b+c<=a = "not a triangle"
      | otherwise = "no"
