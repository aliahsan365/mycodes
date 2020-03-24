absValue :: Int -> Int
absValue x
    | x < 0 = -1 * x
    | otherwise = x

power :: Int -> Int -> Int
power x p
    | p == 0 = 1
    | otherwise = x * power x (p-1)


--isPrime :: Int -> Bool


slowFib :: Int -> Int
slowFib 0 = 0
slowFib 1 = 1
slowFib n = slowFib (n-1) + slowFib (n-2)




quickFib :: Int -> Int
quickFib n = snd (fib n)
	where
		
		fib 1 = (0,1)
		fib i = (f1,f1+f2)
			where
				(f2,f1) = fib (i-1)
