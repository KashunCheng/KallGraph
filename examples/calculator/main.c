
#include <stdio.h>
#include <stdlib.h>

/* A few simple operations */
int add(int a, int b)   { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide_op(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Division by zero!\n");
        exit(EXIT_FAILURE);
    }
    return a / b;
}

/* Typedef for a binary‐op function pointer */
typedef int (*op_t)(int, int);

/* Table of all candidates */
op_t ops[] = { add, subtract, multiply, divide_op };
const char *op_names[] = { "add", "subtract", "multiply", "divide" };
const size_t n_ops = sizeof(ops) / sizeof(*ops);

/* Helper that takes a function pointer as callback */
int apply(op_t f, int x, int y) {
    return f(x, y);
}

/* Chooses an operation by index, then calls it */
int do_operation(size_t idx, int x, int y) {
    if (idx >= n_ops) {
        fprintf(stderr, "Invalid operation index %zu\n", idx);
        exit(EXIT_FAILURE);
    }
    op_t chosen = ops[idx];
    printf("Chosen op: %s\n", op_names[idx]);
    return chosen(x, y);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <op_index> <a> <b>\n", argv[0]);
        fprintf(stderr, "  op_index in [0..%zu]\n", n_ops - 1);
        return EXIT_FAILURE;
    }

    size_t idx = strtoul(argv[1], NULL, 10);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    /* Direct dynamic call via table */
    int result1 = do_operation(idx, a, b);
    printf("Result via table: %d\n", result1);

    /* Indirect call via apply() helper */
    op_t f = ops[idx];
    int result2 = apply(f, a, b);
    printf("Result via callback: %d\n", result2);

    return EXIT_SUCCESS;
}
