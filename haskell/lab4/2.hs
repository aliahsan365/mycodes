data Tree a = Node a (Tree a) (Tree a) | Empty deriving (Show)

t7 = Node 7 Empty Empty
t6 = Node 6 Empty Empty
t5 = Node 5 Empty Empty
t4 = Node 4 Empty Empty
t3 = Node 3 t6 t7
t2 = Node 2 t4 t5
t1 = Node 1 t2 t3
t1' = Node 1 t3 t2

size :: Tree a -> Int 
size Empty = 0
size (Node _ a1 a2) = 1 +  size a1 + size a2

height :: Tree a -> Int
height Empty = 0
height (Node _ a1 a2) = 1 +  max (height a1)  (height a2)

equal :: Eq a => Tree a -> Tree a -> Bool 
equal Empty Empty = True
equal Empty _ = False
equal _ Empty = False
equal (Node a a1 a2) (Node b b1 b2) = a == b && equal a1 b1 && equal a2 b2

isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic Empty _ = False
isomorphic _ Empty = False
isomorphic (Node a a1 a2) (Node b b1 b2) =
    ((a==b) && ((isomorphic a1 b1) && (isomorphic a2 b2))) ||
    ((a==b) && ((isomorphic a1 b2) && (isomorphic a2 b1)))

preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node a a1 a2) = [a] ++ preOrder a1 ++ preOrder a2

postOrder :: Tree a -> [a] 
postOrder Empty = []
postOrder (Node a a1 a2) =  postOrder a1 ++ postOrder a2 ++ [a] 

inOrder  :: Tree a -> [a] 
inOrder Empty = []
inOrder  (Node a a1 a2) =  inOrder  a1 ++ [a] ++ inOrder  a2 




breadthFirst':: [Tree a]-> [a]
breadthFirst' [] = []
breadthFirst' ((Empty):cola) = breadthFirst' cola
breadthFirst' ((Node a a1 a2):cola) = 
    [a] ++ breadthFirst' (cola ++ [a1] ++  [a2]) 


breadthFirst :: Tree a -> [a]
breadthFirst x = breadthFirst' [x]

build :: Eq a => [a] -> [a] -> Tree a

build [] [] = Empty
