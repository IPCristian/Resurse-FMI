main = putStrLn "Hello, world!"
poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x ^ 2 + b * x + c

poly3 x = case x of
    2 -> "doi"
    otherwise -> "nu doi"

eeny x =
    if even x == True then "eeny"
        else "meeny"

fizzbuzz :: Integer -> String
fizzbuzz x =
    if x `mod` 15 == 0 then "FizzBuzz"
        else if x `mod` 3 == 0 then "Fizz"
            else if x `mod` 5 == 0 then "Buzz"
                else ""

tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci n = tribonacci (n-1) + tribonacci (n-2) + tribonacci (n-3)

binomial :: Integer -> Integer -> Integer
binomial n k =
    if n == 0 then 0
        else if k == 0 then 1
            else binomial (n-1) k + binomial (n-1) (k-1)

verifL :: [Int] -> Bool
verifL v = if length v `mod` 2 == 0 then True else False

takefinal :: [Int] -> Int -> [Int]
takefinal v nr =
    if length v < nr then v
        else drop (length v - nr) v

remove :: [Int] -> Int -> [Int]
remove v nr = concat [(take (nr-1) v),(drop nr v)]

myreplicate :: Integer -> Integer -> [Integer]
myreplicate 0 v = []
myreplicate n v = v : (myreplicate (n-1) v)

sumImp :: [Integer] -> Integer
sumImp [] = 0
sumImp (h:t) =
    if odd h == True then h + sumImp t
        else sumImp t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h:t) =
    if head h == 'A' then length h + totalLen t
        else totalLen t
