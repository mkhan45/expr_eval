const std = @import("std");

const BinOp = enum {
    add,
    sub,
    mul,
    div,
};

const ExprTy = enum {
    atomic,
    binary,
};

const BinaryExpr = struct {
    op: BinOp,
    lhs: *const Expr,
    rhs: *const Expr,
};

const Expr = union(ExprTy) {
    atomic: isize,
    binary: BinaryExpr,
};

fn eval(expr: *const Expr) isize {
    return switch (expr.*) {
        ExprTy.atomic => |v| v,
        ExprTy.binary => |b| {
            const lhs = eval(b.lhs);
            const rhs = eval(b.rhs);
            return switch (b.op) {
                BinOp.add => lhs + rhs,
                BinOp.sub => lhs - rhs,
                BinOp.mul => lhs * rhs,
                BinOp.div => @divFloor(lhs, rhs),
            };
        }
    };
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    const expr = Expr { 
        .binary = BinaryExpr { 
            .op = BinOp.add,
            .lhs = &Expr { 
                .binary = BinaryExpr {
                    .op = BinOp.mul,
                    .lhs = &Expr { .atomic = 5 },
                    .rhs = &Expr { .atomic = 3 }
                }
            },
            .rhs = &Expr { .atomic = 2 },
        }
    };

    try stdout.print("{d}\n", .{eval(&expr)});
}
