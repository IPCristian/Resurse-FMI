import Data.Char
import Data.List
import Data.Maybe


primes = sieve [2..100]
sieve [] = []
sieve ( p : ps ) = p : sieve [ x | x <- ps , mod x p /= 0 ]
-- [2] => sieve [3,5,7,9,..]
-- [2,3] => sieve [5,7,11,13..]


numbers = [1 ,2 ,3 ,4 ,5]
total = foldl (-) 6 numbers -- ((((6 -1) -2) -3) -4) -5) = -9
total2 = foldr (-) 6 numbers -- 1- (2- (3- (4- (5-6)))) = -3
doubled = map (* 2) numbers

qsort :: Ord a => [ a ] -> [ a ]
qsort [ ] = [ ]
qsort ( p : xs ) =
    ( qsort lesser ) ++ [ p ] ++ ( qsort greater )
        where
            lesser = filter ( < p ) xs
            greater = filter (>= p ) xs

{- Comentarii pe mai multe linii -}

unu = let a=1;b=2 in a+b
doi = let {a=1;b=2} in a+b
x = let x=1;y=2 in x+y

testare :: [Int] -> [Int] -> [(Int,Int)]
testare [] _ = []
testare _ [] = []
testare (x:xs) (y:ys) = (x,y) : testare xs ys
-- [1,2,3] [4,5,6] => [(1,4),(2,5),(3,6)]


ex1 :: [Char] -> [Char] -> [Char]
ex1 [] _ = []
ex1 _ [] = []
ex1 (x:xs) (y:ys) = if (x == y) then x : ex1 xs ys else []



ex2 :: [Int] -> [Int] -> Int
ex2 x y = if (length x == length y) then ex2ajut x y else error "The lists aren't of equal length."

ex2ajut :: [Int] -> [Int] -> Int
ex2ajut [] _ = 0
ex2ajut (x:xs) (y:ys) = (x*x*y*y) + ex2ajut xs ys

-- ex2 [1,2,3,4] [1,2,3] => Arunca eroare
-- ex2 [1,2,3,4] [5,6,7,8] => 1634
-- ex2 [1,2,3] [0,1,2] => 40

mylist :: [Either Int String]
mylist = [Left 4, Left 1, Right "hello", Left 2, Right " ", Right "world", Left 17]

fctlist :: [Either Int String] -> String
fctlist [] = ""
fctlist (x:xs) = case x of
      Left a -> fctlist xs
      Right b -> b ++ fctlist xs

data PairInt = P Int Int deriving Show
data MyList = L [PairInt] deriving Show
data Exp = I Int | Add Exp Exp | Mul Exp Exp deriving Show

class MyClass m where
  toExp :: m -> Exp

instance MyClass MyList where
  toExp (L []) = I 1
  toExp (L ((P x1 x2) : xs)) = Mul (Add (I x1) (I x2)) (toExp (L xs))

eval :: MyList -> Int
eval list = evalExp $ toExp list

evalExp :: Exp -> Int
evalExp (I x) = x
evalExp (Add x y) = (evalExp x) + (evalExp y)
evalExp (Mul x y) = (evalExp x) * (evalExp y)

myreplicate :: Int -> Int -> [Int]
myreplicate x 1 = [x]
myreplicate x y = x : myreplicate x (y-1)

sumimp :: [Int] -> Int
sumimp x = sum ( filter (odd) x )

myzip3 _ _ [] = []
myzip3 _ [] _ = []
myzip3 [] _ _ = []
myzip3 (x:xs) (y:ys) (z:zs) = (x,y,z) : myzip3 xs ys zs

firstEl l = map (\(x,y) -> x) l

data MyData a b = MyData a b b
instance Functor (MyData a) where fmap f (MyData x y z) = MyData x (f y) (f z)








