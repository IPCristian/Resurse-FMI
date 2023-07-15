import Data.Monoid

data BinaryTree a =
  Leaf a
  | Node ( BinaryTree a ) ( BinaryTree a )
    deriving Show

foldTree :: ( a -> b -> b ) -> b -> BinaryTree a -> b
foldTree f i ( Leaf x ) = f x i
foldTree f i (Node l r ) = foldTree f ( foldTree f i r ) l

myTree = Node (Node ( Leaf 1) ( Leaf 2) ) (Node ( Leaf 3) (Leaf 4) )

instance Foldable BinaryTree where
  foldr = foldTree

-- foldMap :: Monoid m => (a -> m) -> t a -> m
-- foldr :: (a -> b -> b ) -> b -> [a] -> b

-- 1
elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem x xs = foldr (\y acc -> x == y || acc) False xs

elem2 :: (Foldable t, Eq a) => a -> t a -> Bool
elem2 x xs = getAny $ foldMap (\y -> Any (y == x)) xs

-- 3 [1, 2, 3, 4]
-- or $ elem 3 []
-- or [False, False, True, False]

null :: (Foldable t) => t a -> Bool
null x = foldr (\y acc -> False && acc) True x 
-- null x = foldr (\y acc -> False) True x 

-- [Null, Null]

null2:: (Foldable t) => t a -> Bool
null2 x = getAll $ foldMap (\y -> All False) x

lengthRec [] = 0
lengthRec (x:xs) = 1 + lengthRec xs 

length :: (Foldable t) => t a -> Int
length x = foldr (\y acc -> 1+acc) 0 x

length2 :: (Foldable t) => t a -> Int
length2 x = getSum $ foldMap (\y -> Sum 1 ) x 

toList :: (Foldable t) => t a -> [a]
toList x = foldr (\y acc -> [y]++acc) [] x

toList2 :: (Foldable t) => t a -> [a]
toList2 x = foldMap (\y -> [y]) x

-- myTree = Node (Node ( Leaf 1) ( Leaf 2) ) (Node ( Leaf 3) (Leaf 4) )
-- toList myTree -> [1, 2, 3, 4]

fold :: (Foldable t, Monoid m) => t m -> m
fold xs = foldMap (\y -> y) xs
-- fold xs = foldMap id xs
-- Hint: folosiți foldMap

-- 2

{-
data Constant a b = Constant b
instance Functor (Constant a) where
    fmap f (Constant b) = Constant (f b)
-}

data Constant a b = Constant b
instance Foldable (Constant a) where 
    foldMap f (Constant b) = f b

exConst = foldMap Sum (Constant 3)
exConst2 = foldMap Any (Constant False)

data Two a b = Two a b
instance Foldable (Two a) where
    foldMap f (Two a b) = f b

exTwo = foldMap Sum (Two 1 2)

data Three a b c = Three a b c
instance Foldable (Three a b) where
    foldMap f (Three x y z) = f z

exThree = foldMap Sum (Three 1 2 3)

{-
data Three' a b = Three' a b b
instance Functor (Three' a) where
  fmap f (Three' a b1 b2) = Three' a (f b1) (f b2)
-}

data Three' a b = Three' a b b
instance Foldable (Three' a) where 
    foldMap f (Three' a b1 b2) = f b1 <> f b2

exThree' = foldMap Sum (Three' 1 2 3)

data Four' a b = Four' a b b b
instance Foldable (Four' a) where
    foldMap f (Four' x y z t) = f y <> f z <> f t

exFour' = foldMap Sum (Four' 4 5 6 7)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Foldable GoatLord where
    foldMap f NoGoat = mempty
    foldMap f (OneGoat a) = f a
    foldMap f (MoreGoats a b c) = foldMap f a <> foldMap f b <> foldMap f c

exGoat = foldMap Sum (MoreGoats (OneGoat 4) NoGoat (MoreGoats (OneGoat 3) (OneGoat 6) NoGoat))
exGoat2 = foldr (*) 1 (MoreGoats (OneGoat 4) NoGoat (MoreGoats (OneGoat 3) (OneGoat 6) NoGoat))
