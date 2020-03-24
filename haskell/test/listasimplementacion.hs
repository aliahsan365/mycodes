-----el tipo lista.
-- The list type

-- | @since 2.01
instance Functor [] where
    {-# INLINE fmap #-}
    fmap = map

-- See Note: [List comprehensions and inlining]
-- | @since 2.01
instance Applicative [] where
    {-# INLINE pure #-}
    pure x    = [x]
    {-# INLINE (<*>) #-}
    fs <*> xs = [f x | f <- fs, x <- xs]
    {-# INLINE liftA2 #-}
    liftA2 f xs ys = [f x y | x <- xs, y <- ys]
    {-# INLINE (*>) #-}
    xs *> ys  = [y | _ <- xs, y <- ys]

-- See Note: [List comprehensions and inlining]
-- | @since 2.01
instance Monad []  where
    {-# INLINE (>>=) #-}
    xs >>= f             = [y | x <- xs, y <- f x]
    {-# INLINE (>>) #-}
    (>>) = (*>)
    {-# INLINE fail #-}
    fail _              = []
