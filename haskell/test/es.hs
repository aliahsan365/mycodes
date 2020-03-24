
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
