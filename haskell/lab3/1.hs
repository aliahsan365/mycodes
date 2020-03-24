
myFoldl :: (a -> b -> a) -> a -> [b] -> a 
myFoldl _ a [] = a
myFoldl f a (b:bs) = myFoldl f (f a b) bs

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ b [] = b
myFoldr f b (a:as) = f a (myFoldr f b as) 
