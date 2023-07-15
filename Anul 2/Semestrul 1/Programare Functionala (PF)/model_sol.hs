
{-
Grile
1. a
2. c
3. a
4. a
5. a
6. a
7. a
8. a
9. a
10. a
 
-}

{-

Sa se scrie o functie care primeste ca argumente doua siruri de caractere, si
afiseaza cel mai lung prefix comun.
f “sirulnr1” “sirdoi” = “sir”

-}

prefixComun :: String -> String -> String
prefixComun "" _ = ""
prefixComun _ "" = ""
prefixComun (x:xs) (y:ys)
  | x == y = x : (prefixComun xs ys)
  | otherwise = ""

{-
Sa se scrie o functie care pentru doua liste, x si y, calculeaza suma produselor
xi^2 * yi^2 cu xi din x si yi din y. Daca listele au lungimi diferite, functia va
arunca o eroare.
-}
calculeaza :: [Int] -> [Int] -> Int
calculeaza xs ys = if length xs == length ys then sum [x^2*y^2| (x,y)<- zip xs ys] else error "Lungimi diferite"


{-
Se dau urmatoarele tipuri de date:
-}
data PairInt = P Int Int deriving Show

data MyList = L [PairInt] deriving Show

data Exp = I Int | Add Exp Exp | Mul Exp Exp deriving Show

class MyClass m where
  toExp :: m -> Exp

{-
MyList reprezinta lista de perechi, unde o pereche este reprezentata de tipul PairInt.
Exp reprezinta expresii formate din numere intregi si operatiile de adunare si inmultire.
a) Sa se scrie o instanta a clasei MyClass pentru tipul MyList astfel incat functia toExp
sa transforme o lista de perechi astfel: o pereche devine adunare intre cele doua
elemente, iar intre elementele listei se aplica operatia de inmultire. Pentru lista vida
puteti considera ca expresia corespunzatoare este I 1.
Ex: toExp ( L [ P 1 2, P 2 3 , P 5 3] ) == Mul (Add (I 1) (I 2)) (Mul (Add (I 2) (I 3)) (Mul (Add (I 5) (I 3)) (I 1)))
-}

instance MyClass MyList where
  toExp (L []) = I 1
  toExp (L ((P x1 x2):xs)) = Mul (Add (I x1) (I x2)) (toExp (L xs))

{-
b) Sa se scrie o functie eval :: MyList -> Int care are ca parametru o lista de tipul
MyList, transforma lista in expresie si apoi evalueaza expresia rezultata.
-}

eval :: MyList -> Int
eval list = evalExp $ toExp list

evalExp :: Exp -> Int
evalExp (I i) = i
evalExp (Add x1 x2) = evalExp x1 + evalExp x2
evalExp (Mul x1 x2) = evalExp x1 * evalExp x2
