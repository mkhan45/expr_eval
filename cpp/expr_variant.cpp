#include <iostream>
#include <variant>
#include <memory>

enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
};

struct AtomicExpr;
struct BinaryExpr;

using Expr = std::variant<AtomicExpr, BinaryExpr>;

struct AtomicExpr { 
    int val; 
    AtomicExpr(int val) : val(val) {}
};

struct BinaryExpr { 
    BinOp op;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;

    BinaryExpr(BinOp op, Expr lhs, Expr rhs) {
        this->op = op;
        this->lhs = std::make_shared<Expr>(lhs);
        this->rhs = std::make_shared<Expr>(rhs);
    }
};

int eval(const Expr& e);

struct EvalVisitor {
    int result;

    void operator()(const AtomicExpr& e) {
        result = e.val;
    }

    void operator()(const BinaryExpr& e) {
        int lhs = eval(*e.lhs);
        int rhs = eval(*e.rhs);

        switch (e.op) {
            case Add: result = lhs + rhs; break;
            case Sub: result = lhs - rhs; break;
            case Mul: result = lhs * rhs; break;
            case Div: result = lhs / rhs; break;
        }
    }
};

int eval(const Expr& e) {
    auto visitor = EvalVisitor { 0 };
    std::visit(visitor, e);
    return visitor.result;
}

int main() {
    Expr e = BinaryExpr(Add, AtomicExpr(3), BinaryExpr(Mul, AtomicExpr(5), AtomicExpr(8)));
    std::cout << eval(e) << std::endl;
}
