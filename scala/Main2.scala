abstract class Expr
case class AtomicExpr(value: Int) extends Expr
case class BinaryExpr(op: (Int, Int) => Int, lhs: Expr, rhs: Expr) extends Expr

object Main2 {
    def eval(expr: Expr): Int = {
        expr match {
            case AtomicExpr(value) => value

            case BinaryExpr(op, lhs, rhs) => op(eval(lhs), eval(rhs))
        }
    }

    def main(args: Array[String]) = {
        println(eval(BinaryExpr((a, b) => a + b, AtomicExpr(1), AtomicExpr(2))))
    }
}
