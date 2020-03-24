divisors :: Int -> [Int]
divisors d = [x | x <- [1..d], d `mod` x == 0]

nbDivisors :: Int -> Int 
nbDivisors = length . divisors


moltCompost :: Int -> Bool
moltCompost n = and [nbDivisors x < nbDivisors n | x <- [2..n-1]]


dalt x = iterate ((**) x) 1
baix = scanl  (*) 1 [1..]

exps :: Float -> [Float]
exps x = zipWith (/) (dalt x) baix


--func2 = \ e x y -> e >= abs( x - y )

exponencial :: Float -> Float -> Float
exponencial x e = sum $ takeWhile (>= e) (exps x) 

    
        
convert :: Char -> Int
convert 'I' = 1
convert 'V' = 5
convert 'X' = 10
convert 'L' = 50
convert 'C' = 100
convert 'D' = 500
convert 'M' = 1000
convert '0' = 0

roman2int :: String -> Int 
roman2int [] = 0
roman2int (x:[]) = convert x
roman2int (x:y:xs)
    | convert x >= convert y = abs (convert x + roman2int (y:xs))
    | otherwise =  abs (convert x - roman2int (y:xs))



f :: Int -> (Char,Char) -> Int
f t (x,y)
    | convert x == 0 = convert y + t
    | convert y == 0 = convert  x + t
    | convert x >= convert y = abs (convert x + t)
    | otherwise =  abs(convert x - t)

roman2int' :: String -> Int 
roman2int' no = foldl f 0 (zip (no ++ ['0']) (['0'] ++ no))

            



taylorarrels :: Float -> Float -> Float
taylorarrels x n = 0.5*(n+(x/n))
--es cm hacer + 2 5 = (+2) 5, solo que la primera es con x , q es cte.
--la n se va calculando cada vez.la pos tiene que ver cn la pos de
--(taylorarrels x) , el iterate te calcula el siguente usando el anterior cm arg
--NOTA: muy importante el orden de los args.
arrels :: Float -> [Float]
arrels x = iterate (taylorarrels x) x


func = \e x ->  e <= abs((fst x) - (snd x))


arrel :: Float -> Float -> Float
arrel x e = snd (head (dropWhile (func e) pares))
    where
        pares = zip (arrels x) (tail (arrels x))





   

data LTree a = Leaf a | Node (LTree a) (LTree a)

--a tiene que ser algo mostrable 
--(algo para lo que el show x default ya valga),
-- un int , un string etc..., y por eso la condicion de Show a. 
instance Show a => Show  (LTree a) where
    show (Leaf x) = "{" ++ (show $ x) ++ "}"
    show (Node a1 a2) =  "<" ++ (show a1) ++  "," ++  (show a2) ++ ">"
