import Data.Char

myLength :: [Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs



myMaximum :: [Int] -> Int
myMaximum [x] = x
myMaximum (x:xs)
    | x > myMaximum xs = x
    | otherwise = myMaximum xs

suma :: [Int] -> Int
suma [] = 0
suma (x:xs) = x + suma xs 
 

average :: [Int] -> Float
average [] = fromIntegral 0
average l = (fromIntegral $ suma  l) / (fromIntegral $ myLength l)  



myreverse  :: [Int] -> [Int]
myreverse [] = []
myreverse [x] = [x]
myreverse (x:xs) = (myreverse xs) ++ [x]


buildPalindrome :: [Int] -> [Int]
buildPalindrome l = myreverse l ++ l

flatten :: [[Int]] -> [Int]
flatten [] = []
flatten [x] = x
flatten (x:xs) =  x ++ flatten  xs


remove' :: [Int] -> Int -> [Int]
remove' [] _ = []
remove' (x:xs) e
    |x == e =  remove' xs e
    |otherwise = [x] ++ remove' xs e



remove :: [Int] -> [Int] -> [Int]
remove [] _ = []
remove l [] = l
remove l (x:xs) = remove (remove' l x) xs 



selectpares :: [Int] -> [Int]
selectpares [] = []
selectpares  (x:xs)
    |(x `mod` 2) == 0 = [x] ++ selectpares xs
    | otherwise = selectpares xs
    
selectimpares :: [Int] -> [Int]
selectimpares [] = []
selectimpares (x:xs)
    |(x `mod` 2) == 0 = selectimpares xs
    | otherwise = [x] ++ selectimpares xs    
    

oddsNevens :: [Int] -> ([Int],[Int])
oddsNevens l =  (simpares,spares)
    where
        spares = selectpares l
        simpares = selectimpares l






--primeDivisors :: Int -> [Int] 
--primeDivisors n = primeDivisors' 
        







