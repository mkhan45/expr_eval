defmodule Expr do
    def eval(expr) do
        case expr do
            {op, lhs, rhs} -> case op do
                :add -> eval(lhs) + eval(rhs)
                :sub -> eval(lhs) - eval(rhs)
                :mul -> eval(lhs) * eval(rhs)
                :div -> eval(lhs) / eval(rhs)
            end
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
