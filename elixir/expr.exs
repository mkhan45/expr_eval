defmodule Expr do
    def eval(expr) do
        case expr do
            {:add, lhs, rhs} -> eval(lhs) + eval(rhs)
            {:sub, lhs, rhs} -> eval(lhs) - eval(rhs)
            {:mul, lhs, rhs} -> eval(lhs) * eval(rhs)
            {:div, lhs, rhs} -> eval(lhs) / eval(rhs)
            n -> n
        end
    end
end

defmodule Main do
    def main do
        expr = {:add, 3, {:mul, 15, {:sub, 4, 2}}}
        res = Expr.eval(expr)
        IO.puts(res)
    end
end

Main.main()
