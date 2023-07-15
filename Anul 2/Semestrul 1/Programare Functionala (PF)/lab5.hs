firstEl1 :: [(a,b)] -> [a]
firstEl1 y = map (\x -> (fst x)) y

sumList :: [[Int]] -> [Int]
sumList y = map sum y

modif :: Int -> Int
modif x = if even x == True then x `div` 2 else x*2

pre12 :: [Int] -> [Int]
pre12 y = map (\x -> modif x) y

verif :: Char -> String -> String
verif a b = if (elem a b == True) then b else []

ex4 :: Char -> [String] -> [String]
ex4 a b = filter (/= "") (map (\x -> verif a x) b)

patrat :: Int -> Int
patrat x = if (x `mod` 2 == 1) then x*x else 0

patratimp :: [Int] -> [Int]
patratimp y = filter (/= 0) (map (\x -> patrat x) y)

verific :: (Int,Int) -> Int
verific (a,b) = if (b `mod` 2 == 1) then a*a else 0

patratpozimp :: [Int] -> [Int]
patratpozimp y = filter (/= 0) (map verific (zip y [1..]))

verifvoc :: Char -> Bool
verifvoc x = if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' || x == 'A'
   || x == 'E' || x == 'I' || x == 'O' || x == 'U') then True else False

numaiVocale :: [String] -> [String]
numaiVocale y = map (\x -> filter verifvoc x) y

mymap :: (a->b) -> [a] -> [b]
mymap op (x:xs) = op x : mymap op xs
mymap op [] = []

myfilter :: (a->Bool) -> [a] -> [a]
myfilter op (a:as) = if (op a == True) then a : myfilter op as else myfilter op as
myfilter op [] = []

ex9 :: [Int] -> Int
ex9 x = foldr (+) 0 (map (\y -> y^2) (filter odd x))

isTrue :: [Bool] -> Bool
isTrue x = foldr (&&) True x

rmChar :: Char -> String -> String
rmChar a x = filter (/= a) x

rmCharsRec :: String -> String -> String
rmCharsRec (x:xs) a = rmCharsRec xs (rmChar x a)
rmCharsRec x [] = []
rmCharsRec [] a = a

rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr rmChar s2 s1
