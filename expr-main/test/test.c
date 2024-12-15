#include "../include/expr.h"
#include "../include/common.h"

void TestExpr();
void TestCheckParentheses();
void mainLoop();

int main(int argc, char *argv[]){
    if (argc < 2) {
        TestExpr();
        TestCheckParentheses();
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "e") == 0) {
                TestExpr();
            } else if (strcmp(argv[i], "c") == 0) {
                TestCheckParentheses();
            } else if (strcmp(argv[i], "r") == 0) {
                mainLoop();
            }
        }
    }
    return 0;
}

void TestExpr(){
    char str[2 * MAX];
    char expression[MAX];
    bool success = true;
    int ans;
    // open file exprTest.txt
    FILE *fp = fopen("../test/exprTest.txt", "r");
    if(fp == NULL){
        printf("File not found\n");
        return;
    }
    // read expression, success indicator, and correct answer from file
    while(fgets(str, 2 * MAX, fp) != NULL){
        // use strtok to split the string
        char *token = strtok(str, ";");
        if (token != NULL) {
            strncpy(expression, token, MAX);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            success = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            ans = atoi(token);
        }
        // calculate the expression
        bool success_test = true;
        int res = expr(expression, &success_test);
        // judge whether the result is the same as the correct answer
        if(res == ans && success_test == success){
            printf("Correct\n");
        }else{
            printf("Wrong\n");
        }
    }
    fclose(fp);
}

void TestCheckParentheses(){
    bool success = true;
    bool valid = true;
    char str[2 * MAX];
    char expression[MAX];
    // open file checkParenthesesTest.txt
    FILE *fp = fopen("../test/checkParenthesesTest.txt", "r");
    if(fp == NULL){
        printf("File not found\n");
        return;
    }
    // read expression, success indicator, and valid indicator from file
    while(fgets(str, 2 * MAX, fp) != NULL){
        // use strtok to split the string
        char *token = strtok(str, ";");
        if (token != NULL) {
            strncpy(expression, token, MAX);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            valid = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token != NULL) {
            success = atoi(token);
        }
        // check the parentheses
        bool success_test = true;
        bool valid_test = true;
        if (!make_token(expression)) {
            printf("Invalid expression\n");
        }
        bool res = check_parentheses(0, strlen(expression), &valid_test);
        // judge whether the result is the same as the correct answer
        if(res == success && valid_test == valid){
            printf("Correct\n");
        }else{
            printf("Wrong\n");
        }
    }
    fclose(fp);
}

void mainLoop() {
    char str[2*MAX], expression[MAX], command;
    printf("Welcome to the calculator!\n");
    printf("commands:\n");
    printf("p: evaluate the expression and print its value\n");
    printf("q: quit the calculator\n");
    bool flag = true;
    while(flag) {
        printf("(Calculator) ");
        fflush(stdout);
        gets(str);
        sscanf(str, "%c", &command);
        switch (command) {
            case 'p': {
                strcpy(expression, str + 2);
                bool success = true;
                int res = expr(expression, &success);
                if (success) {
                    printf("%d\n", res);
                } else {
                    printf("Invalid expression\n");
                }
                break;
            }
            case 'q': {
                flag = false;
                break;
            }
            default: {
                printf("Invalid command\n");
                break;
            }
        }
    }
}