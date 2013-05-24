import Data.Time.Calendar.OrdinalDate

main = do
  line <- getLine
  let year = read line :: Integer
  putStrLn $ if (isLeapYear year) then "yes" else "no"
