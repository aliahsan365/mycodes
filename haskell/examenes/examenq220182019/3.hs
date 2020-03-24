
data STree a = Nil | Node Int a (STree a) (STree a) deriving Show

t1 = Node 3 99 (Node 1 88 Nil Nil) (Node 1 22 Nil Nil)
t2 = Node 2 77 (Node 1 33 Nil Nil) Nil
t3 = Node 6 44 t1 t2
t4 = Node 7 55 t1 t2


sumanodos :: STree a -> Int
sumanodos (Nil) = 0
sumanodos (Node _ _ a1 a2) = 1 + (sumanodos a1) + (sumanodos a2)  



isOk :: STree a -> Bool
isOk (Nil) = True
isOk (Node t _ a1 a2) = (1 + (sumanodos a1) + (sumanodos a2) == t) && (isOk a1) && (isOk a2)
