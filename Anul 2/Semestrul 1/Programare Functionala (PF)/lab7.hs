data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10;
listaFructe = [Mar "Ionatan" False,
              Portocala "Sanguinello" 10,
              Portocala "Valencia" 22,
              Mar "Golden Delicious" True,
              Portocala "Sanguinello" 15,
              Portocala "Moro" 12,
              Portocala "Tarocco" 3,
              Portocala "Moro" 12,
              Portocala "Valencia" 2,
              Mar "Golden Delicious" False,
              Mar "Golden" False,
              Mar "Golden" True]

soiuri = ["Tarocco", "Moro", "Sanguinello"]

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala s _) = elem s soiuri
ePortocalaDeSicilia (Mar _ _) = False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (Portocala x y:xs) = if elem x soiuri then y + nrFeliiSicilia xs else nrFeliiSicilia xs
nrFeliiSicilia (Mar _ _:xs) = nrFeliiSicilia xs

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (Mar _ x:xs) = if x == True then 1 + nrMereViermi xs else nrMereViermi xs
nrMereViermi (Portocala _ _:xs) = nrMereViermi xs

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
  deriving Show

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Caine _ x) = Just x
rasa (Pisica _) = Nothing

data Linie = L [Int]
  deriving Show
data Matrice = M [Linie]
  deriving Show

verifica :: Matrice -> Int -> Bool
verifica (M x) n = foldr (&&) True (map ajutor x)
  where ajutor x = verifica2 x n

verifica2 :: Linie -> Int -> Bool
verifica2 (L x) n = if sum x == n then True else False

doarPozN :: Matrice -> Int -> Bool
doarPozN (M x) n = foldr (&&) True (map ajutor [ y | y <-x, lengthLine y == n])
  where ajutor x = doarPozLine x

lengthLine :: Linie -> Int
lengthLine (L []) = 0
lengthLine (L(x:xs)) = 1 + lengthLine (L xs)

doarPozLine :: Linie -> Bool
doarPozLine (L []) = True
doarPozLine (L (x:xs)) = if x > 0 then doarPozLine (L xs) else False

corect :: Matrice -> Bool
corect (M(x:xs)) = corect2 (lengthLine x) (M xs)

corect2 :: Int -> Matrice -> Bool
corect2 x (M []) = True
corect2 x (M(y:ys)) = if (lengthLine y == x) then corect2 x (M ys) else False
