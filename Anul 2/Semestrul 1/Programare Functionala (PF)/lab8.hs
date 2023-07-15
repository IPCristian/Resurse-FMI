import Data.Maybe

type Nume = String
data Prop
 = Var Nume
 | F
 | T
 | Not Prop
 | Prop :|: Prop
 | Prop :&: Prop
 | Prop :->: Prop
 | Prop :<->: Prop
 deriving Eq
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :|: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

instance Show Prop where
 show (Var x) = x
 show F = "False"
 show T = "True"
 show (Not x) = "(~" ++ show (x) ++ ")"
 show (x :|: y) = "(" ++ show(x) ++ "|" ++ show(y) ++ ")"
 show (x :&: y) = "(" ++ show(x) ++ "&" ++ show(y) ++ ")"
 show (x :->: y) = "(" ++ show(x) ++ "->" ++ show(y) ++ ")"
 show (x :<->: y) = "(" ++ show(x) ++ "<->" ++ show(y) ++ ")"

test_ShowProp :: Bool
test_ShowProp = show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var x) env = impureLookup x env
eval (F) env = False
eval (T) env = True
eval (Not x) env = not (eval x env)
eval (x :|: y) env = eval x env || eval y env
eval (x :&: y) env = eval x env && eval y env
eval (x :->: y) env = eval x env <= eval y env
eval (x :<->: y) env = eval x env == eval y env

test_eval =
 eval (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

test_eval2 = eval  (Not (Var "P" :|: Var "Q") :&: T) [("P", True), ("Q", False)] == False

variabile :: Prop -> [Nume]
variabile (Var x) = [x]
variabile (Not x) = variabile x
variabile (x :|: y) = (variabile x) ++ (variabile y)
variabile (x :&: y) = (variabile x) ++ (variabile y)
variabile (x :->: y) = (variabile x) ++ (variabile y)
variabile (x :<->: y) = (variabile x) ++ (variabile y)

test_variabile =
 variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs [] = [[]]
envs (x:xs) = [ (x,False) : e | e <- envs xs] ++ [ (x,True) : e | e <- envs xs]

test_envs = envs ["P", "Q"]
 ==
 [ [ ("P",False)
 , ("Q",False)
 ]
 , [ ("P",False)
 , ("Q",True)
 ]
 , [ ("P",True)
 , ("Q",False)
 ]
 , [ ("P",True)
 , ("Q",True)
 ]
 ]

satisfiabila :: Prop -> Bool
satisfiabila k = or ( [ eval k y | y<-envs(variabile k)] )

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida k = and ( [ eval k y | y<-envs(variabile k)] )

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

echivalenta :: Prop -> Prop -> Bool
echivalenta a b =
  if (variabile(a) == variabile(b)) then and ([ eval a y == eval b y | y<-envs(variabile(a))])
  else and ([i == j | i<-[ eval a y | y<-envs(variabile(a))] , j<-[eval b y | y<-envs(variabile(b))]])

test_echivalenta1 =
  True
  ==
    (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))

test_echivalenta2 =
  False
  ==
    (Var "P") `echivalenta` (Var "Q")

test_echivalenta3 =
  True
  ==
  (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))
