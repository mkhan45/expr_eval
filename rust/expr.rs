enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
}

enum Expr<'a> {
    AtomicExpr { val: isize },
    BinaryExpr {
        op: BinOp,
        lhs: &'a Expr<'a>,
        rhs: &'a Expr<'a>,
    },
}

impl<'a> Expr<'a> {
    fn eval(&self) -> isize {
        use Expr::*;

        match self {
            AtomicExpr { val } => *val,
            BinaryExpr { op, lhs, rhs } => match op {
                BinOp::Add => lhs.eval() + rhs.eval(),
                BinOp::Sub => lhs.eval() - rhs.eval(),
                BinOp::Mul => lhs.eval() * rhs.eval(),
                BinOp::Div => lhs.eval() / rhs.eval(),
            }
        }
    }
}

fn main() {
    let expr = Expr::BinaryExpr {
        op: BinOp::Add,
        lhs: &Expr::AtomicExpr { val: 5 },
        rhs: &Expr::BinaryExpr {
            op: BinOp::Mul,
            lhs: &Expr::AtomicExpr { val: 12 },
            rhs: &Expr::AtomicExpr { val: 4 },
        },
    };

    println!("{}", expr.eval());
}
