#include "../include/common.h"
#include "../include/expr.h"

token tokens[MAX];

enum {
    TK_NUM
    };

int num_token;

bool make_token(const char str[]) {
    num_token = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            i++;
            continue;
        }
        if (str[i] == '+') {
            tokens[num_token].type = '+';
            tokens[num_token++].value = 0;
        } else if (str[i] == '-') {
            tokens[num_token].type = '-';
            tokens[num_token++].value = 0;
        } else if (str[i] == '*') {
            tokens[num_token].type = '*';
            tokens[num_token++].value = 0;
        } else if (str[i] == '/') {
            tokens[num_token].type = '/';
            tokens[num_token++].value = 0;
        } else if (str[i] == '(') {
            tokens[num_token].type = '(';
            tokens[num_token++].value = 0;
        } else if (str[i] == ')') {
            tokens[num_token].type = ')';
            tokens[num_token++].value = 0;
        } else if (isdigit(str[i])) {
            tokens[num_token].type = TK_NUM;
            tokens[num_token].value = 0;
            while (isdigit(str[i])) {
                tokens[num_token].value = tokens[num_token].value * 10 + str[i] - '0';
                i++;
            }
            num_token++;
            i--;
        } else {
            printf("Invalid character\n");
            return false;
        }
        i++;
    }
    return true;
}

bool check_parentheses(int p, int q, bool *success) {
    /* Check if the expression is surrounded by a pair of parentheses
     * p, q are the positions of the first and last tokens
     * If the expression is surrounded by a pair of parentheses, return true
     * Otherwise, return false
     * besides, if the expression is invalid, set *success to false
     * */
    /* TODO: complete this function */
    return true;
}

int eval(int p, int q, bool *success) { // p, q are the positions of the first and last tokens
    /* TODO: complete this function */
    if (p > q) {
        /* the expression is invalid */
    }
    if (p == q) {
        /* single token
         * the token should be a number
         * if the token is a number, return the value of the number
         * */
    }
    if (check_parentheses(p, q, success) == true) {
        /* check if the expression is surrounded by a pair of parentheses
         * if it is, just remove the parentheses and call eval recursively
         */
        return eval(p + 1, q - 1, success);
    }
    /* Now, you need to find the dominant operator */
    int op = -1; // the position of dominant operator
    int op_type = -1; // the type of dominant operator
    /* you need to find the dominant operator and change the value of op and op_type correctly */


    int val1 = eval(p, op - 1, success);
    int val2 = eval(op + 1, q, success);

    switch (op_type) {
        case '+': return val1 + val2;
        case '-':
        case '*':
        case '/':
        default: assert(0); // use assert() to abort the program, you can change it if necessary
    }
    return 0;
}

int expr(char *e, bool *success) {
    if (!make_token(e)) {
        *success = false;
        return 0;
    }
    return eval(0, num_token - 1, success);
}