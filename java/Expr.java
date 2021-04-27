enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
}

public abstract class Expr {
    abstract int eval();

    static class AtomicExpr extends Expr {
        int val;

        int eval() {
            return val;
        }

        public AtomicExpr(int val) {
            this.val = val;
        }
    }

    static class BinaryExpr extends Expr {
        BinOp op;
        Expr lhs;
        Expr rhs;

        int eval() {
            return switch (op) {
                case Add -> lhs.eval() + rhs.eval();
                case Sub -> lhs.eval() - rhs.eval();
                case Mul -> lhs.eval() * rhs.eval();
                case Div -> lhs.eval() / rhs.eval();
            };
        }

        public BinaryExpr(BinOp op, Expr lhs, Expr rhs) {
            this.op = op;
            this.lhs = lhs;
            this.rhs = rhs;
        }
    }

    public static void main(String[] args) {
        Expr e = new BinaryExpr(BinOp.Mul, new AtomicExpr(5), new AtomicExpr(10));
        System.out.println(e.eval());
    }
}
