#include <stdio.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"
#include "utils.h"
#define MAX_SIZE 200

void test_precedence();
void test_validate_string();
void test_infix2postfix();

int main(void) {
#ifdef TEST_PRECEDENCE
    test_precedence();
#endif
#ifdef TEST_INFIX2POSTFIX
    test_infix2postfix();
#endif
#ifdef TEST_VALIDATE
    test_validate_string();
#endif
    return 0;
}

void test_precedence() {
    const char operators[] = {'(', '+', '-', '/', '*', 'Q', 'C', 'S', 'T', 'G', 'L', '~'};
    const int result[] = {0, 1, 1, 2, 2, 3, 4, 4, 4, 4, 4, 5};
    printf("Foo := int precedence(char *operator)\n");
    for (int i = 0; i < 12; i++) {
        printf("Test:= %d\n", i);
        if (precedence(operators[i]) == result[i]) {
            printf("SUCCES\n");
        } else
            printf("FAIL\n");
    }
}
void test_validate_string() {
    char *str = "22.1+cos(-sin(202*x))";
    char *out = malloc(sizeof(char) * MAX_SIZE);
    printf("Foo := string2infix\nIn := 22.1+cos(-sin(202*x))\nOut := 22.1 + C ( ~ S ( 202 * x ) ) \n");
    if (validate_string(str, out)) {
        printf("%s", out);
    }
    free(out);
}

void test_infix2postfix() {
    // char *str = "cos(sin(2*x))";
    char *str = "sin(x)";
    char *out = malloc(sizeof(char) * MAX_SIZE);
    char *infix = malloc(sizeof(char) * MAX_SIZE);
    validate_string(str, out);
    infix2postfix(out, infix);
    printf("%s", infix);
    free(out);
    free(infix);
}
