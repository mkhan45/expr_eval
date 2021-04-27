enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
}

enum Expr {
    AtomicExpr { val: isize },
    BinaryExpr {
        op: BinOp,
        lhs: Box<Expr>,
        rhs: Box<Expr>,
    },
}

impl Expr {
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
        lhs: Box::new(Expr::AtomicExpr { val: 5 }),
        rhs: Box::new(Expr::BinaryExpr {
            op: BinOp::Mul,
            lhs: Box::new(Expr::AtomicExpr { val: 12 }),
            rhs: Box::new(Expr::AtomicExpr { val: 4 }),
        }),
    };

    println!("{}", expr.eval());
}
