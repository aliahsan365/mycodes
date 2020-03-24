

dalt x = iterate ((**) x) 1
baix = scanl  (*) 1 [1..]

exps :: Float -> [Float]
exps x = zipWith (/) (dalt x) baix


exponencial :: Float -> Float -> Float
exponencial x e = sum $ takeWhile (>= e) (exps x) 
