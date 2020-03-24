convert :: Char -> Int
convert 'I' = 1
convert 'V' = 5
convert 'X' = 10
convert 'L' = 50
convert 'C' = 100
convert 'D' = 500
convert 'M' = 1000
convert '0' = 0

--apartado 1
roman2int :: String -> Int 
roman2int [] = 0
roman2int (x:[]) = convert x
roman2int (x:y:xs)
    | convert x >= convert y = abs (convert x + roman2int (y:xs))
    | otherwise =  abs (convert x - roman2int (y:xs))

--apartado 2



-- apartado 3

taylorarrels :: Float -> Float -> Float
taylorarrels x n = 0.5*(n+(x/n))
--es cm hacer + 2 5 = (+2) 5, solo que la primera es con x , q es cte.
--la n se va calculando cada vez.la pos tiene que ver cn la pos de
--(taylorarrels x) , el iterate te calcula el siguente usando el anterior cm arg
--NOTA: muy importante el orden de los args.
arrels :: Float -> [Float]
arrels x = iterate (taylorarrels x) x


--apartado 4


func = \e x ->  e <= abs((fst x) - (snd x))


arrel :: Float -> Float -> Float
arrel x e = snd (head (dropWhile (func e) pares))
    where
        pares = zip (arrels x) (tail (arrels x))


--apartado 5
data LTree a = Leaf a | Node (LTree a) (LTree a)

--a tiene que ser algo mostrable 
--(algo para lo que el show x default ya valga),
-- un int , un string etc..., y por eso la condicion de Show a. 
instance Show a => Show  (LTree a) where
    show (Leaf x) = "{" ++ (show $ x) ++ "}"
    show (Node a1 a2) =  "<" ++ (show a1) ++  "," ++  (show a2) ++ ">"
