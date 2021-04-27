#include <iostream>
#include <memory>

enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
};

struct OhNo {};

class Expr {
    public:
        virtual int eval() const { throw OhNo{}; };
};

class AtomicExpr : public Expr {
    public:
        int val;

        AtomicExpr(const int val) { this->val = val; }
        int eval() const override {
            return this->val;
        }
};

class BinaryExpr : public Expr {
    public:
        BinOp op;
        std::unique_ptr<Expr> lhs;
        std::unique_ptr<Expr> rhs;

        BinaryExpr(const BinOp op, Expr* lhs, Expr* rhs) {
            this->op = op;
            this->lhs = std::unique_ptr<Expr>(lhs);
            this->rhs = std::unique_ptr<Expr>(rhs);
        }

        int eval() const override {
            switch (this->op) {
                case Add: return lhs->eval() + rhs->eval();
                case Sub: return lhs->eval() - rhs->eval();
                case Mul: return lhs->eval() * rhs->eval();
                case Div: return lhs->eval() / rhs->eval();
                default: throw "Unimplemented";
            }
        }
};

int main() {
    const Expr* e = new BinaryExpr(Mul, new AtomicExpr(5), new BinaryExpr(Add, new AtomicExpr(3), new AtomicExpr(1)));
    std::cout << e->eval() << std::endl;
}
