import Data.Maybe

type Name = String

data Value = VBool Bool
  |VInt Int
  |VFun (Value -> Value)
  |VError

data Hask = HTrue | HFalse
  |HIf Hask Hask Hask
  |HLit Int
  |Hask :==: Hask
  |Hask :+: Hask
  |HVar Name
  |HLam Name Hask
  |Hask :$: Hask
  |Hask :*: Hask

infix 4 :==:
infixl 6 :+:
infixl 8 :*:
infixl 9 :$:

type HEnv = [(Name, Value)]

-- 1.
instance Show Value where
  show (VBool x) = show (x)
  show (VInt x) = show (x)
  show (VFun _) = show ("Nu se pot afisa functii")
  show (VError) = show ("Nu se pot afisa erori")

-- 2.
instance Eq Value where
  (VBool x) == (VBool y) = x == y
  (VInt x) == (VInt y) = x == y
  (VInt x) == (VBool y) = if (x > 0 && y) then True else if (x < 0 && y == False) then True else False
  (VBool x) == (VInt y) = if (y > 0 && x) then True else if (y < 0 && x == False) then True else False
  _ == (VFun _) = error "Nu putem compara valori cu functii"
  (VFun _) == _ = error "Nu putem compara valori cu functii"

-- 3.
hEval :: Hask -> HEnv -> Value
hEval HTrue r     = VBool True
hEval HFalse r      = VBool False
hEval (HIf c d e) r = hif (hEval c r) (hEval d r) (hEval e r)
  where hif (VBool b) v w = if b then v else w
        hif _ _ _ = error "Nu s-a putut realiza operatia if pe tipurile de date primite"
hEval (HLit x) r = VInt x
hEval (HVar a) r
    | (lookup a r) /= Nothing = y
    | otherwise = error "Nu a putut fi gasit"
        where Just y = lookup a r
hEval (h1 :+: h2) r = hplus (hEval h1 r) (hEval h2 r)
  where hplus (VInt v1) (VInt v2) = VInt (v1+v2)
        hplus _ _ = error "Nu se pot aduna tipurile de date primite"
hEval (h1 :*: h2) r = hinm (hEval h1 r) (hEval h2 r)
  where hinm (VInt v1) (VInt v2) = VInt (v1*v2)
        hinm _ _ = error "Nu se pot inmulti tipurile de date primite"
hEval (h1 :==: h2) r = hegal (hEval h1 r) (hEval h2 r)
  where hegal (VInt v1) (VInt v2) = VBool (v1 == v2)
        hegal (VBool v1) (VBool v2) = VBool (v1 == v2)
        hegal _ _ = error "Nu se pot egala tipurile de date primite"
hEval (HLam n h) r = VFun (\v -> hEval h ((n,v):r))
hEval (h1 :$: h2) r = hfun (hEval h1 r) (hEval h2 r)
  where hfun (VFun fct1) x = fct1 x
        hfun _ _ = error "Unul din parametrii primiti nu reprezinta o functie"

-- 4.
run :: Hask -> String
run pg = show (hEval pg [])

h0 =  (HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y"))))
      :$: (HLit 3)
      :$: (HLit 4)

test_h0 = (hEval h0 []) == (VInt 7)
