import Data.Char
import Data.List


-- 1.
rotate :: Int -> [Char] -> [Char]
rotate n x = if (n < 0 || n > length(x)) then error "invalid n" else z ++ y
    where (y,z) = splitAt n x

-- 2.
prop_rotate :: Int -> String -> Bool
prop_rotate k str = rotate (l - m) (rotate m str) == str
                        where l = length str
                              m = if l == 0 then 0 else k `mod` l

-- 3.
makeKey :: Int -> [(Char, Char)]
makeKey x = zip "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (rotate x "ABCDEFGHIJKLMNOPQRSTUVWXYZ")

-- 4.
lookUp :: Char -> [(Char, Char)] -> Char
lookUp a ((x,y):xs) = if (x == a) then y else lookUp a xs
lookUp a [] = a

-- 5.
encipher :: Int -> Char -> Char
encipher a x = lookUp x (makeKey a)

-- 6.
normalize :: String -> String
normalize (x:xs) = if (elem x "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890") then x : normalize xs
                   else if (elem x "abcdefghijklmnopqrstuvwxyz") then toUpper x : normalize xs
                   else normalize xs
normalize "" = ""

-- 7.
encipherStr :: Int -> String -> String
encipherStr x a = encipherStr2 x (normalize a)

encipherStr2 :: Int -> String -> String
encipherStr2 x (y:ys) = encipher x y : encipherStr2 x ys
encipherStr2 x "" = ""

-- 8.
reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey ((a,b):xs) = (b,a) : reverseKey xs
reverseKey [] = []

-- 9.
decipher :: Int -> Char -> Char
decipher a x = lookUp x (reverseKey (makeKey a))

decipherStr :: Int -> String -> String
decipherStr x (y:ys) = if (elem y "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890") then decipher x y : decipherStr x ys else decipherStr x ys
decipherStr x "" = ""
