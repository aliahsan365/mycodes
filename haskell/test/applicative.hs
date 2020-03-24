instance Applicative [] where
    pure = []
    (<*>) = map


instance Applicative [] where
    {-# INLINE pure #-}
    pure x    = [x]
    {-# INLINE (<*>) #-}
    fs <*> xs = [f x | f <- fs, x <- xs]
    {-# INLINE liftA2 #-}
    liftA2 f xs ys = [f x y | x <- xs, y <- ys]
    {-# INLINE (*>) #-}
    xs *> ys  = [y | _ <- xs, y <- ys]
