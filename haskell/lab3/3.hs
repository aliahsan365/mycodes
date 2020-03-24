
ones :: [Integer]
ones = [1] ++  ones 


nats :: [Integer]
nats = iterate (+1) 0

--se aplica
--0 1
--1 1
--2 1
--3 1
--4 1
--5 1
--etc...



negativos :: [Integer]
negativos = map (*(-1)) [0..] 


ints'' :: [(Integer,Integer)]
ints'' = zip negativos (tail nats)


clist :: (Integer,Integer) -> [Integer]
clist par = [fst par] ++ [snd par] 



ints' :: [[Integer]]
ints' = map clist ints''

ints  :: [Integer]
ints  = concat ints'
     
     
     
triangulars :: [Integer]

triangulars = 0:zipWith (+) (tail nats) triangulars



factorials :: [Integer]

factorials = 1:zipWith (*) (tail nats) (factorials)
