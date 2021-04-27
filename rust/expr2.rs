#![feature(box_syntax)]

enum Expr {
    AtomicExpr { val: isize },
    BinaryExpr {
        op: Box<dyn Fn(isize, isize) -> isize>,
        lhs: Box<Expr>,
        rhs: Box<Expr>,
    },
}

impl Expr {
    fn eval(&self) -> isize {
        use Expr::*;

        match self {
            AtomicExpr { val } => *val,
            BinaryExpr { op, lhs, rhs } => (*op)(lhs.eval(), rhs.eval()),
        }
    }
}

fn main() {
    use Expr::*;

    let expr = BinaryExpr {
        op: box |a, b| a + b,
        lhs: box AtomicExpr { val: 5 },
        rhs: box BinaryExpr {
            op: box |a, b| a * b,
            lhs: box AtomicExpr { val: 3 },
            rhs: box AtomicExpr { val: 4 },
        },
    };

    println!("{}", expr.eval());
}
