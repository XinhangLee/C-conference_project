#ifndef EXPR_H
#define EXPR_H
#include <stdbool.h>

#define MAX 1000

typedef struct {
    int type;
    int value;
} token;

int expr(char *e, bool *success);
bool check_parentheses(int start, int end, bool *success);
bool make_token(const char str[]);

#endif
