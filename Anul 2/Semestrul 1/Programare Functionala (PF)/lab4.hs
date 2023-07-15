main = putStrLn "Hello, world!"

factori :: Int -> [Int]
factori x = [ y | y<-[1..x], x `mod` y == 0]

prim :: Int -> Bool
prim x = if (factori x == [1,x]) then True else False

numerePrime :: Int -> [Int]
numerePrime x = [ y | y<-[2..x] , prim y == True]

myzip3 :: [Int] -> [Int] -> [Int] -> [[(Int,Int,Int)]]
myzip3 [] b c = []
myzip3 a [] c = []
myzip3 a b [] = []
myzip3 (a:as) (b:bs) (c:cs) = [(a,b,c)] : myzip3 as bs cs 

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat l = and [ x<y | (i1,x) <- zip [0..] l, (i2,y) <- zip [0..] l, i1<i2]

ordonataNat2 :: [Int] -> Bool
ordonataNat2 [] = True
ordonataNat2 [x] = True
ordonataNat2 (x:xs) = if (x < head xs) then ordonataNat2 xs else False

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] op = True
ordonata [x] op = True
ordonata (x:xs) op = if op x (head xs) == True then ordonata xs op else False

(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (a,b) (c,d) = if (a < c && b < d) then True else False

compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList fct [] = []
compuneList fct (x:xs) = (fct.x) : compuneList fct xs

aplicaList :: a -> [(a->b)] -> [b]
aplicaList a [] = []
aplicaList a (x:xs) = (x a) : aplicaList a xs 


