data Expr
    = Atomic Int
    | Binary (Int -> Int -> Int) Expr Expr

eval :: Expr -> Int
eval (Atomic v) = v
eval (Binary op lhs rhs) = op (eval lhs) (eval rhs)

main = do
    print $ eval (Binary (+) (Atomic 3) (Binary (*) (Atomic 4) (Atomic 5)))
