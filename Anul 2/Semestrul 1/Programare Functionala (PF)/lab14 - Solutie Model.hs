-- I. Grile
{-
1. Pentru a instantia clasa Eq trebuie sa implementam urmatoarele functii
a) ==
b) eq
c) ==, =, , =
d) eq, not
e) ==, =
r a

2. Ce constrangeri de tipuri trebuie sa adaugam la functia f pentru ca urmatorul cod sa fie
corect
data MyData a b = MyData a b b
f  MyData a b - MyData a b - Bool
f (MyData x1 y1 z1) (MyData x2 y2 z2 ) = x1 == x2 && y1 == y2 && z1 == z2
a) codul este deja corect
b) Eq a
c) Eq a, Eq b
d) Eq a, Ord a
r c

3. Se defineste
data MyData a b = MyData a b b
Care instanta de mai jos este corecta
a) instance Functor (MyData a) where
fmap f (MyData x y z) = MyData x (f y) (f z)
b) instance Functor (MyData a) where
fmap f (MyData x y z) = MyData (f x) (f y) (f z)
c) instance Functor (MyData a b) where
fmap f (MyData x y z) = MyData x (f y) (f z)
d) instance Functor (MyData a b) where
fmap f (MyData x y z) = MyData (f x) (f y) (f z)
r a

4. Se defineste
data MyData a b = Data1 a  Data2 b
Care instanta de mai jos este corecta
a) instance Functor (MyData a) where
fmap f (Data1 x) = Data1 x
fmap f (Data2 x) = Data2 (f x)
b) instance Functor (MyData a) where
fmap f (Data1 x) = Data1 (f x)
fmap f (Data2 x) = Data2 (f x)
c) instance Functor (MyData a b) where
fmap f (Data1 x) = Data1 (f x)
fmap f (Data2 x) = Data2 (f x)
d) instance Functor (MyData a b) where
fmap f (Data1 x) = Data1 x
fmap f (Data2 x) = f (Data2 x)
r a

5. Care instanta Monoid de mai jos este corecta
newtype MyBool = MyBool Bool
deriving (Eq, Show)
a) instance Semigroup MyBool where
    MyBool x  MyBool y = MyBool ( x && y )
instance Monoid MyBool where
    mempty = MyBool True
b) instance Monoid MyBool where
    MyBool x  MyBool y = MyBool ( x && y )
    mempty = MyBool True
c) instance Semigroup MyBool where
    MyBool x  MyBool y = MyBool ( x  y )
instance Monoid MyBool where
    mempty = MyBool True
d) nu se poate face instanta Monoid pentru tipul MyBool.
r a

6. Care instanta Monoid de mai jos este corecta
newtype MyInt = MyInt Int
deriving (Eq, Show)
a) instance Semigroup MyInt where
    MyInt x  MyInt y = MyInt ( x + y + 1)
instance Monoid MyInt where
    mempty = MyInt (-1)
b) instance Semigroup MyInt where
    MyInt x  MyInt y = MyInt ( x + y + 1)
instance Monoid MyInt where
    mempty = MyInt 0
c) instance Semigroup MyInt where
    MyInt x  MyInt y = MyInt ( x + y + 1)
    mempty = MyInt (-1)
d) nu se poate face instanta Monoid pentru tipul MyInt
r a

7. Se defineste
data MyData a b = MyData a b b
Care instanta de mai jos este corecta
a) instance Foldable (MyData a) where
foldMap f (MyData x y z) = mempty  f y  f z
b) instance Foldable (MyData a) where
foldMap f (MyData x y z) = f z
c) instance Foldable (MyData a b) where
foldMap f (MyData x y z) = f y  f z
d) instance Foldable (MyData a) where
foldMap f (MyData x y z) = f x  f y  f z
r a

8. Se defineste
data MyData a b = Data1 a  Data2 b
Care instanta de mai jos este corecta
a) instance Foldable (MyData a) where
foldMap f (Data1 x) = mempty
foldMap f (Data2 x) = f x
b) instance Foldable (MyData a) where
foldMap f (Data1 x) = f x
foldMap f (Data2 x) = f x
c) instance Foldable (MyData a) where
foldMap f (Data1 x) = Data1 x
foldMap f (Data2 x) = f x
d) instance Foldable (MyData a b) where
foldMap f (Data1 x) = Data1 x
foldMap f (Data2 x) = f x
r a

9. Ce se obtine dupa instructiunea [ ( + 1) , (^2) ]  [ 1 , 2 , 3, 4]
a) [2,3,4,5,1,4,9,16]
b) instructiune invalida
c) [2,3,4,5]
d) [1,4,9,16]
r a

10. Ce se obtine dupa instructiunea (+10)  [1..5]
a) instructiune invalida
b) [11, 12,13,14,15]
c) [10,20,30,40,50]
d) [1,2,3,4,5]
r a 
-}

-- II. Liste
-- 1
prefixComun  String - String - String
prefixComun  _ = 
prefixComun _  = 
prefixComun (xxs) (yys)
   x == y = x  (prefixComun xs ys)
   otherwise = 

-- 2
calculeaza  [Int] - [Int] - Int
calculeaza xs ys = if length xs == length ys then sum [x^2y^2 (x,y)- zip xs ys] else error Lungimi diferite

-- III. Tipuri de date
data PairInt = P Int Int deriving Show

data MyList = L [PairInt] deriving Show

data Exp = I Int  Add Exp Exp  Mul Exp Exp deriving Show

class MyClass m where
  toExp  m - Exp

-- a
instance MyClass MyList where
  toExp (L []) = I 1
  toExp (L ((P x1 x2)xs)) = Mul (Add (I x1) (I x2)) (toExp (L xs))

-- b
eval  MyList - Int
eval list = evalExp $ toExp list

evalExp  Exp - Int
evalExp (I i) = i
evalExp (Add x1 x2) = evalExp x1 + evalExp x2
evalExp (Mul x1 x2) = evalExp x1  evalExp x2
