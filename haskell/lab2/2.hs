
flatten :: [[Int]] -> [Int] 
flatten ll = foldl (++) [] ll 

myLength :: String -> Int 
myLength palabra = sum (map (const 1) palabra)


myReverse :: [Int] -> [Int] 
myReverse l = foldl (flip (:)) [] l


countIn :: [[Int]] -> Int -> [Int]

countIn ll x = map f ll
    where
        f l = length (filter (== x) l)  
-- f = \l ....

---no cojes hasta la primera letra
-- coges hasta el primer blanco

firstWord :: String -> String

firstWord palabra  = takeWhile (/=' ') $ dropWhile (==' ') palabra 







 



