#include <stdio.h>
#include <stdlib.h>

void free_expr();
int eval_expr();

typedef enum expr_ty {
    Atomic,
    Binary,
} expr_ty;

typedef enum bin_op {
    Add,
    Sub,
    Mul,
    Div,
} bin_op;

typedef struct atomic_expr {
    int val;
} atomic_expr_t;

typedef struct binary_expr {
    enum bin_op op;
    struct expr* lhs;
    struct expr* rhs;
} binary_expr_t;

typedef struct expr {
    expr_ty ty;
    union {
        atomic_expr_t atomic;
        binary_expr_t* binary;
    };
} expr_t;

void free_binary_expr(binary_expr_t* expr) {
    free_expr(expr->lhs);
    free_expr(expr->rhs);
    free(expr);
}

void free_expr(expr_t* expr) {
    switch (expr->ty) { 
        case Atomic: free(expr); break;
        case Binary: free_binary_expr(expr->binary); free(expr); break;
    }
}

int eval_binary_expr(const binary_expr_t* expr) {
    switch (expr->op) {
        case Add: return eval_expr(expr->lhs) + eval_expr(expr->rhs);
        case Sub: return eval_expr(expr->lhs) - eval_expr(expr->rhs);
        case Mul: return eval_expr(expr->lhs) * eval_expr(expr->rhs);
        case Div: return eval_expr(expr->lhs) / eval_expr(expr->rhs);
    }
}

int eval_expr(const expr_t* expr) {
    switch (expr->ty) {
        case Atomic: return expr->atomic.val;
        case Binary: return eval_binary_expr(expr->binary);
    }
}

expr_t* new_atomic(int v) {
    expr_t* e = malloc(sizeof(expr_t));
    *e = (expr_t) {
        .ty = Atomic,
        .atomic = v,
    };
    return e;
}

expr_t* new_binary(bin_op op, expr_t* lhs, expr_t* rhs) {
    binary_expr_t* data = malloc(sizeof(binary_expr_t));
    *data = (binary_expr_t) {
        .op = op,
        .lhs = lhs,
        .rhs = rhs,
    };

    expr_t* e = malloc(sizeof(expr_t));
    *e = (expr_t) {
        .ty = Binary,
        .binary = data,
    };

    return e;
}

int main() {
    expr_t* expr = new_binary(Add, new_atomic(12), new_binary(Mul, new_atomic(3), new_atomic(5)));
    printf("%d\n", eval_expr(expr));
    free_expr(expr);
}
