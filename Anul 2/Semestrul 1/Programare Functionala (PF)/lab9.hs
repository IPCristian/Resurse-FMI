sfChr :: Char -> Bool
sfChr a = if (a == '.' || a == '?' || a == ':' || a == '!') then True else False

nrProp :: [Char] -> Int
nrProp [] = 0
nrProp (x:xs) = if (sfChr x == True) then (1 + nrProp xs) else nrProp xs

nrProp2 :: [Char] -> Int
nrProp2 k = sum [ if (sfChr x == True) then 1 else 0 | x<-k ]

pozitive :: [Int] -> Bool
pozitive k = and [ x>0 | x<-k ]

liniiN :: [[Int]] -> Int -> Bool
liniiN m n = and (map pozitive (filter (\x -> length x == n) m))

data Punct = Pt [Int]
  deriving Show

data Arb = Vid | F Int | N Arb Arb
  deriving Show

class ToFromArb a where
  toArb :: a -> Arb
  fromArb :: Arb -> a

instance ToFromArb Punct where
  toArb (Pt (x:[])) = N (F x) Vid
  toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))
  fromArb (N (F x) Vid) = Pt [x]
  fromArb (N (F x) y) = Pt (x:k) where Pt k = fromArb y
