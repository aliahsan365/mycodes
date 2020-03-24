
import Debug.Trace

class Pred a where
    sat :: a -> Bool
    unsat :: a -> Bool
    
    unsat = not . sat
    
data Arbin a = Buit | Node a (Arbin a) (Arbin a) deriving(Show)


instance  Pred Int where
    sat 0 = False
    sat _ = True    

instance  Pred a => Pred (Arbin a) where
    sat Buit = True
    sat (Node x fe fd) = sat x && sat fe && sat fd

--infinitesat :: [Bool]

--infinitesat = map sat [0..]

arbolsat :: Arbin Int  -> Bool
arbolsat a = sat a

--                       n    d
data Racional = Racional Int Int  deriving (Eq, Show)



