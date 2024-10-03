#include <stdio.h>
#include <string.h>

#include "geometry.h"
#include "parsing.h"
#include "utils.h"

#define ERROR_INPUT_VALIDATION_FAILED 1
#define ERROR_CONVERSION_TO_POSTFIX_FAILED 2

void handle_failure(int failure);

int main(void) {
    char* original_expression = read_string();
    char* infix = allocate_string(16);  // 16 * 64 chars = 1024
    infix[0] = '\0';
    int failure = 0;
    if (validate_string(original_expression, infix)) {
        char* postfix = allocate_string(16);  // 16 * 64 chars = 1024
        postfix[0] = '\0';
        infix2postfix(infix, postfix);
        if (strlen(postfix) > 0) {
            draw(postfix);
        } else {
            failure = ERROR_CONVERSION_TO_POSTFIX_FAILED;
        }
        free(postfix);
    } else {
        failure = ERROR_INPUT_VALIDATION_FAILED;
    }
    free(original_expression);
    free(infix);
    handle_failure(failure);
    return 0;
}

void handle_failure(int failure) {
    switch (failure) {
        case 0:
            getchar();  // Wait for user's response
            break;
        case ERROR_INPUT_VALIDATION_FAILED:
            printf("Input data validation failed");
            break;
        case ERROR_CONVERSION_TO_POSTFIX_FAILED:
            printf("Conversion from infix to postfix failed");
            break;
        default:
            printf("Unknown error");
            break;
    }
    printf("\n");
}
