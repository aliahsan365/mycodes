--eql :: [Int] -> [Int] -> Bool
--eql [] [] = True
--eql [] _ = False
--eql _ [] = False
--eql (x:xs) (y:ys)
--    | x==y = True && eql xs ys && (length xs == length ys)
--   | otherwise = False
    

--prod :: [Int] -> Int 



eql :: [Int] -> [Int] -> Bool
eql l1 l2 =  (and (zipWith f l1 l2)) && (length l1 == length l2)
    where
        f = ( == )


prod :: [Int] -> Int 
prod  l = foldl (*) 1 l


prodOfEvens :: [Int] -> Int
prodOfEvens l = prod (filter even l)


powersOf2 :: [Int] 
powersOf2 = iterate f 1 
    where
        f =  (*2)

scalarProduct :: [Float] -> [Float] -> Float 
scalarProduct l1 l2 = foldl (+) 0 (zipWith (*) l1 l2) 

