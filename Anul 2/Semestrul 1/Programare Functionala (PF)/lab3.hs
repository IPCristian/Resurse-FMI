import Data.Char
main = putStrLn "Hello, world!"

palindrom :: String -> Bool
palindrom x = (reverse x == x)

vocala :: Char -> Bool
vocala x = elem x "aeiouAEIOU"

nr :: String -> Int
nr "" = 0
nr (h:t) = if vocala h == True then 1 + nr t else nr t

par :: Int -> Bool
par x = if mod x 2 == 0 then True else False

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h:t) = if palindrom h == True then nr h + nrVocale t else nrVocale t

f :: Int -> [Int] -> [Int]
f x [] = []
f x (h:t) = if par h == True then [h,x] ++ f x t else [h] ++ f x t

divizori :: Int -> [Int]
divizori x = [y | y <- [1..x] , x `mod` y == 0]

listadiv :: [Int] -> [[Int]]
listadiv [] = []
listadiv (h:t) = divizori h : listadiv t

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec a b [] = []
inIntervalRec a b (h:t) = if h >= a && h <= b then [h] ++ inIntervalRec a b t else inIntervalRec a b t

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b x = [ z | z <- x, z>=a, z<=b ]

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t) = if h > 0 then 1 + pozitiveRec t else pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp x = length [ y | y<-x, y>0]

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec x = pozitiiImpareRec2 0 x

pozitiiImpareRec2 :: Int -> [Int] -> [Int]
pozitiiImpareRec2 a [] = []
pozitiiImpareRec2 a (h:t) = if par h == False then [a] ++ pozitiiImpareRec2 (a+1) t else pozitiiImpareRec2 (a+1) t

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp x = pozitiiImpareComp2 (zip x [0..100])

pozitiiImpareComp2 :: [(Int,Int)] -> [Int]
pozitiiImpareComp2 x = [ snd y |  y<-x, par (fst y) == False ]

multDigitsRec :: [Char] -> Int
multDigitsRec [] = 0
multDigitsRec (h:t) = if h>='0' && h<='9' then digitToInt h * multDigitsRec t else multDigitsRec t

multDigitsComp :: [Char] -> Int
multDigitsComp x =  produs [ digitToInt y | y<-x, isDigit y == True]

produs :: [Int] -> Int
produs [] = 1
produs (h:t) = h * produs t