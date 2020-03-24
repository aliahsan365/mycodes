
import Data.Char


myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl _ a [] = a
myFoldl f a (b:bresto) = myFoldl f (f a b) bresto 


myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ b [] = b
myFoldr f b (a:aresto) = f a (myFoldr f b aresto)

myIterate :: (a -> a) -> a -> [a]
myIterate f a = a:myIterate f (f a)

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil p f a
    | (p  a) == True = a
    | (p  (f a)) == True = f a
    | otherwise = myUntil p f (f a)



myMap :: (a -> b) -> [a] -> [b]
myMap f la = [f a | a <- la]  


myFilter :: (a -> Bool) -> [a] -> [a]
myFilter p la =  [a | a <- la , p $ a] 


myAll :: (a -> Bool) -> [a] -> Bool
myAll p la = and (myMap p la)

myAny :: (a -> Bool) -> [a] -> Bool
myAny p la = or (myMap p la)  

myZip :: [a] -> [b] -> [(a, b)]
myZip [] _ =[]
myZip _ [] = []
myZip (a:aresto) (b:bresto) = [(a,b)] ++ myZip aresto bresto

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith f la lb = [f a b | (a,b) <- myZip la lb]

countIf :: (Int -> Bool) -> [Int] -> Int
countIf f l = length [a | a<-l, f a == True] 

pam :: [Int] -> [Int -> Int] -> [[Int]]
pam l fl = map f fl
    where
        f fi = map fi l 

--pam2 :: [Int] -> [Int -> Int] -> [[Int]] 
--pam2 l fl = map f fl
--    where
--        f fl 

filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int 
filterFoldl p f a lb = foldl f a (filter p lb)



--insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int] 








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
factorials = 1:zipWith (*) (tail nats) factorials 



fibs :: [Integer]
fibs =  0:1:zipWith (+) fibs (tail fibs)     





----










-------hello/bye

--main = do
--    nom <- getLine
--    if head nom == 'A' || head nom == 'a' then do
--        putStrLn "Hello!"
--    else
--        putStrLn "Bye!"


------IMC


imc :: Float -> Float -> String
imc m h
    | bmi < 18 = "underweight"
    | bmi >= 18 && bmi < 25 = "normal weight"
    | bmi >= 25 && bmi < 30 = "overweight"
    | bmi >= 30 && bmi < 40 = "obese"
    | bmi >= 40 = "severely obese"
        where
            bmi= m / (h*h)
main :: IO()
main = do
    line <- getLine
    if line /= "*" then do
        let nom = head (words line)
        let m = read (head (tail (words line))) :: Float
        let h = read (last (words line)) :: Float
        putStrLn (nom ++ ": " ++ (imc m h))
        main
    else
        return ()
    

--printlista :: [String] -> IO()
--printlista [] =
--printlista (x:xs) = putStrLn x 

---PROBANDO CON MAYBE

data MyMaybe a = MyJust a | MyNothing deriving(Show)

--instance Show a => Show (MyMaybe a) where
--    show MyNothing =  MyNothing
--    show (MyJust a) = show (MyJust a)

instance Eq a => Eq (MyMaybe a) where
    (==) MyNothing MyNothing = True
    (==) (MyJust a) (MyJust b)
        | a == b = True
        | otherwise = False
    (==) _ _ = False

instance Functor (MyMaybe) where
    fmap _ (MyNothing) = MyNothing
    fmap f (MyJust x) = MyJust (f x)



mymaybefunc :: (a -> b) -> MyMaybe a -> MyMaybe b
mymaybefunc f m  = fmap f m

--PROBANDO CON EITHER

data MyEither a b = MyLeft a | MyRight b deriving(Eq,Show)


instance Functor (MyEither a) where
    fmap _ (MyLeft x) = MyLeft x
    fmap f (MyRight x) = MyRight (f x)

--instance (Eq a,Eq b) => Eq (MyEither a) where
--    (==) (MyLeft x)  (MyLeft y)
--        | x == y = True
--        | otherwise = False
--    (==) (MyRight x) (MyRight y)
--        | x == y = True
--        | otherwise = False
--    (==) _ _ = False




--myeitherfunc :: (c -> d) -> (MyEither a b) -> (MyEither c d)
--myeitherfunc f e  = fmap f e

-----ejemplo


type Height = Float
type Width = Float
type Radius = Float
data Rectangle = Rectangle Height Width
data Circle = Circle Radius

class Shape a where
    area :: a -> Float
    perimeter :: a -> Float

 
------expresions


data Expr = Val Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr



eval1 :: Expr -> Int
eval1 (Val x) = x
eval1 (Add e1 e2) = eval1 e1 + eval1 e2
eval1 (Sub e1 e2) = eval1 e1 - eval1 e2
eval1 (Mul e1 e2) = eval1 e1 * eval1 e2
eval1 (Div e1 e2) = eval1 e1 `div` eval1 e2    


eval2 :: Expr -> Maybe Int
eval2 (Val x) = Just x
eval2 (Add e1 e2) = do
    x <- eval2 e1
    y <- eval2 e2
    return (x+y)
eval2 (Sub e1 e2) = do
    x <- eval2 e1
    y <- eval2 e2
    return (x-y)
eval2 (Mul e1 e2) = do
    x <- eval2 e1
    y <- eval2 e2
    return (x*y)
eval2 (Div e1 e2) = do
    x <- eval2 e1
    y <- eval2 e2
    if y == 0 then do
        Nothing
    else 
        return (x `div` y)


eval3 :: Expr -> Either String Int
eval3 (Val x) = Right x
eval3 (Add e1 e2) = do
    x <- eval3 e1
    y <- eval3 e2
    return (x+y)
eval3 (Sub e1 e2) = do
    x <- eval3 e1
    y <- eval3 e2
    return (x-y)
eval3 (Mul e1 e2) = do
    x <- eval3 e1
    y <- eval3 e2
    return (x*y)
eval3 (Div e1 e2) = do
    x <- eval3 e1
    y <- eval3 e2
    if y == 0 then do
        Left "div0"
    else
        Right (x `div` y)    
-- cua 1    
data Queue a = Queue [a] [a] deriving(Show)

create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push a (Queue p1 p2) = Queue p1 (a:p2)

pop :: Queue a -> Queue a
pop (Queue (a:p1) p2) = (Queue p1 p2)               
pop (Queue [] p2) = (Queue (tail (reverse p2)) [])               
      
top :: Queue a -> a
top (Queue [] p2) = head (reverse p2) 
top (Queue (a:p1) p2) = a

empty :: Queue a -> Bool
empty (Queue [] []) = True
empty _ = False


instance Eq a => Eq (Queue a) where
    (==) (Queue a1 a2) (Queue b1 b2) = (a1 ++ reverse a2) == (b1 ++ reverse b2)

---cua 2
--1
instance Functor (Queue) where
    fmap _ (Queue [] []) = (Queue [] [])
    fmap f (Queue p1 p2) = (Queue (map f p1) (map f p2))
--2         
translation :: Num b => b -> Queue b -> Queue b
translation t (Queue p1 p2) = fmap (+t) (Queue p1 p2)
--3
--instance Applicative (Queue) where
   

--instance Monad (Queue) where
--    (>>=) (Queue p1 p2) f = (Queue (concatMap f p1)(concatMap f p2))
--4

----
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



--quickFib :: Int -> Int
--quickFib n = snd (fib n)
--	where
--		
--		fib 1 = (0,1)
--		fib i = (f1,f1+f2)
--			where
--     			(f2,f1) = fib (i-1)

lam = \x y -> x + y + 2



