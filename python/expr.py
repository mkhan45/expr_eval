from enum import Enum

class BinOp(Enum):
    ADD = 0
    SUB = 1
    MUL = 2
    DIV = 3

def eval(expr):
    if (type(expr) == int or type(expr) == float):
        return expr
    elif (type(expr)):
        (op, lhs, rhs) = expr
        op = {
                BinOp.ADD: lambda a, b: a + b,
                BinOp.SUB: lambda a, b: a - b,
                BinOp.MUL: lambda a, b: a * b,
                BinOp.DIV: lambda a, b: a / b,
        }[op]
        return op(eval(lhs), eval(rhs))
    else:
        raise Exception()

e = (BinOp.ADD, 3, (BinOp.MUL, 4, (BinOp.ADD, 2, 3)))
print(eval(e))
