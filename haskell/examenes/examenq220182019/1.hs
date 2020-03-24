
divisors :: Int -> [Int]
divisors d = [x | x <- [1..d], d `mod` x == 0]

nbDivisors :: Int -> Int 
nbDivisors = length . divisors


moltCompost :: Int -> Bool
moltCompost n = and [nbDivisors x < nbDivisors n | x <- [2..n-1]]
