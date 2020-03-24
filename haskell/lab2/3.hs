myMap :: (a -> b) -> [a] -> [b]
myMap f la = [ f x | x <- la]


myFilter :: (a -> Bool) -> [a] -> [a] 

myFilter f l = [ x |x <- l, (f x) == (True)]


myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c] 
myZipWith f la lb = [f a b| a <- la, b <- lb]







