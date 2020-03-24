


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
    Just (x+y) 



