data Avi = Avi {
    nom :: [Char],
    edat :: Int,
    despeses :: [Int]
    } deriving (Show)


avis = [ Avi { nom = "Joan", edat = 68, despeses = [640, 589, 573]}, 
  Avi { nom = "Pepa", edat = 69, despeses = [710,550,570,698,645,512]}, 
  Avi { nom = "Anna", edat = 72, despeses = [530,534]}, 
  Avi { nom = "Pep", edat = 75, despeses = [770,645,630,650,590,481,602]} ]


promigDespeses :: Avi -> Int
promigDespeses a = (fromIntegral (sum (despeses a)))
