myInt = 55555555555555555555555555555555555555555555555555555555555

double :: Integer -> Integer
double x = x + x

maxim :: Integer -> Integer -> Integer
maxim x y =
  if (x > y)
    then x
    else y

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z =
  if (x >= y && x >= z)
    then x
    else if (y >= x && y >= z)
      then y
      else z

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 a b c d =
  let
    u = (maxim a b)
    v = (maxim c d)
  in
    maxim u v

verifmaxim4 :: Integer -> Integer -> Integer -> Integer -> Bool
verifmaxim4 a b c d =
  let
    u = maxim4 a b c d
  in
    if (u >= a && u >= b && u >= c && u >= d)
      then True
    else False

sumpat :: Integer -> Integer -> Integer
sumpat a b = a*a + b*b

paritate :: Integer -> [Char]
paritate a =
  if (mod a 2 == 1)
    then "Impar"
  else "Par"

fact :: Integer -> Integer
fact x =  if (x == 0) then 1 else x * fact (x-1)

verificare :: Integer -> Integer ->  Bool
verificare a b = if (a > 2*b) then True else False
