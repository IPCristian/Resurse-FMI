data Expr = Const Int -- integer constant
  | Expr :+: Expr -- addition
  | Expr :*: Expr -- multiplication
  deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
  | Node Operation Tree Tree -- branch
  deriving (Eq, Show)

-- 1.1
instance Show Expr where
  show (Const x) = show (x)
  show (x :+: y) = "(" ++ show (x) ++ "+" ++ show (y) ++ ")"
  show (x :*: y) = "(" ++ show (x) ++ "*" ++ show (y) ++ ")"

-- 1.2
evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (x :+: y) = evalExp x + evalExp y
evalExp (x :*: y) = evalExp x * evalExp y

exp11 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp21 = (Const 2 :*: (Const 3 :+: Const 4))
exp31 = (Const 4 :+: (Const 3 :*: Const 3))
exp41 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp11 == 6
test12 = evalExp exp21 == 14
test13 = evalExp exp31 == 13
test14 = evalExp exp41 == 16

-- 1.3
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add x y) = evalArb(x) + evalArb(y)
evalArb (Node Mult x y) = evalArb(x) * evalArb(y)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test15 = evalArb arb1 == 6
test16 = evalArb arb2 == 14
test17 = evalArb arb3 == 13
test18 = evalArb arb4 == 16

-- 1.4
expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (x :+: y) = Node Add (expToArb (x)) (expToArb (y))
expToArb (x :*: y) = Node Mult (expToArb (x)) (expToArb (y))

-- 2.1
class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
    :: Ord key
    => key -> value -> c key value -> c key value
  clookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  values :: c key value -> [value]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  keys c = [fst p | p <- toList c]
  values c = [snd p | p <- toList c]
  fromList [] = empty
  fromList (x:xs) = insert k v (fromList xs) where (k,v) = x

-- 2.2
newtype PairList k v
  = PairList { getPairList :: [(k, v)] }

instance Collection PairList where
  empty = PairList []
  singleton k v = PairList [(k,v)]
  insert k v (PairList l) = PairList((k,v) : (filter(\(k1,v) -> k/=k1) l))
  clookup k (PairList l) = lookup k l
  delete k1 (PairList l) = PairList [ (k,v) | (k,v) <- l, k/=k1]
  toList = getPairList

-- 2.3
data SearchTree key value
  = Empty
  | BNode
    (SearchTree key value)  -- elemente cu cheia mai mica
    key                     -- cheia elementului
    (Maybe value)           -- valoarea elementului
    (SearchTree key value)  -- elemente cu cheia mai mare

instance Collection SearchTree where
  empty = Empty
  singleton k v = BNode Empty k (Just v) Empty
  insert k v Empty = BNode Empty k (Just v) Empty
  insert k v (BNode st cheie valoare dr) = if (k < cheie) then insert k v st else insert k v dr
  clookup k (BNode st cheie valoare dr)
    | k == cheie = valoare
    | k < cheie = clookup k st
    | k > cheie = clookup k dr
  delete k (BNode st cheie valoare dr)
    | k == cheie = BNode st cheie Nothing dr
    | k < cheie = delete k st
    | k > cheie = delete k dr
  toList Empty = []
  --toList (BNode st cheie valoare dr) = [(cheie,valoare)] : (toList st) : (toList dr) : [] 
