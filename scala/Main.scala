abstract class BinOp
case object Add extends BinOp
case object Sub extends BinOp
case object Mul extends BinOp
case object Div extends BinOp

abstract class Expr
case class AtomicExpr(value: Int) extends Expr
case class BinaryExpr(op: BinOp, lhs: Expr, rhs: Expr) extends Expr

object Main {
    def eval(expr: Expr): Int = {
        expr match {
            case AtomicExpr(value) => value

            case BinaryExpr(op, lhs, rhs) =>
                op match {
                    case Add => eval(lhs) + eval(rhs)
                    case Sub => eval(lhs) - eval(rhs)
                    case Mul => eval(lhs) * eval(rhs)
                    case Div => eval(lhs) / eval(rhs)
                }
        }
    }

    def main(args: Array[String]) = {
        println(eval(BinaryExpr(Add, AtomicExpr(1), AtomicExpr(2))))
    }
}
