data Op = Add | Sub | Mul | Div

data Expr
    = Atomic Int
    | Binary Op Expr Expr

eval :: Expr -> Int
eval (Atomic v) = v
eval (Binary Add lhs rhs) = (eval lhs) + (eval rhs)
eval (Binary Sub lhs rhs) = (eval lhs) - (eval rhs)
eval (Binary Mul lhs rhs) = (eval lhs) * (eval rhs)
eval (Binary Div lhs rhs) = (eval lhs) `div` (eval rhs)

main = do
    print $ eval (Binary Add (Atomic 3) (Binary Mul (Atomic 2) (Atomic 5)))
