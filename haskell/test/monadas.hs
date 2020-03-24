data Model = Seat127 | TeslaS3 | NissanLeaf | ToyotaHybrid deriving (Eq, Show)
data Etiqueta = Eco | B | C | Cap deriving (Eq, Show)
matricules = [("Joan", 6524), ("Pere", 6332), ("Anna", 5313), ("Laia", 9999)]
models = [(6524, NissanLeaf), (6332, Seat127), (5313, TeslaS3), (7572, ToyotaHybrid)]
etiquetes = [(Seat127, Cap), (TeslaS3, Eco), (NissanLeaf, Eco), (ToyotaHybrid, B)]


etiqueta :: String -> Maybe Etiqueta
etiqueta nom =
    lookup nom matricules >>= \mat ->
    lookup mat models >>= \mod ->
    lookup mod etiquetes

etiqueta' :: String -> Maybe Etiqueta
etiqueta' nom = do
    mat <- lookup nom matricules 
    mod <- lookup mat models 
    lookup mod etiquetes
