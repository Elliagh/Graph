#include "calc.h"

#include <math.h>
#include <string.h>

#include "parsing.h"
#include "stack.h"
#include "utils.h"

double apply_unary_operator(char c, double value, int* failure) {
    double result;
    switch (c) {
        case OPERATOR_UNARY_MINUS:
            result = execute('-', 0, value);
            break;
        case OPERATOR_COS:
            result = execute(OPERATOR_COS, value, 0);
            break;
        case OPERATOR_SIN:
            result = execute(OPERATOR_SIN, value, 0);
            break;
        case OPERATOR_TAN:
            result = execute(OPERATOR_TAN, value, 0);
            break;
        case OPERATOR_CTG:
            result = execute(OPERATOR_CTG, value, 0);
            break;
        case OPERATOR_LOG:
            result = execute(OPERATOR_LOG, value, 0);
            break;
        case OPERATOR_SQRT:
            result = execute(OPERATOR_SQRT, value, 0);
            break;
        default:
            *failure = 1;  // flag invalid unary operator
            result = VALUE_OUT_OF_RANGE;
            break;
    }
    return result;
}

double parse_number(char* postfix_expression, int* i, int* failure) {
    int counter = 0;
    int len = strlen(postfix_expression);
    double number = VALUE_OUT_OF_RANGE;
    char number_as_string[NUMBER_MAX_SYMBOLS] = {'\0'};
    while (is_digit(postfix_expression[*i]) && postfix_expression[*i] != '\0' &&
           counter < NUMBER_MAX_SYMBOLS) {
        number_as_string[counter++] = postfix_expression[*i];
        (*i)++;
    }
    if (!is_digit(postfix_expression[*i]) || *i == len) {  // Reading of a number is done
        number_as_string[counter] = '\0';
        if (1 != sscanf(number_as_string, "%lf", &number)) {  // Number was read
            *failure = 1;                                     // flag invalid parsing
            number = VALUE_OUT_OF_RANGE;
        }
    }
    (*i)--;  // Prevent missing operators and operands

    return number;
}

double calculate(char* postfix_expression, double x) {
    Stack* numbers = NULL;
    int i = -1, len = strlen(postfix_expression), failure = 0;
    while (i < len && !failure) {
        ++i;
        char c = postfix_expression[i];
        if (is_x(c)) {
            push(&numbers, get_double_element(x));
        } else if (is_digit(c)) {
            double number = parse_number(postfix_expression, &i, &failure);
            if (!failure) {
                push(&numbers, get_double_element(number));
            }
        } else if (precedence(c) != -1) {  // A character contains operator
            if (is_unary_operator(c)) {
                Element last = pop(&numbers);
                if (!last.is_empty) {
                    double last_value = 0;
                    last_value = last.value.number;
                    double result_to_push = apply_unary_operator(c, last_value, &failure);
                    if (!failure) {
                        push(&numbers, get_double_element(result_to_push));
                    }
                }
            } else {  // Continue with the rest of operators
                Element b = pop(&numbers), a = pop(&numbers);
                double operation_result =
                    execute(c, a.is_empty ? 0 : a.value.number, b.is_empty ? 0 : b.value.number);
                push(&numbers, get_double_element(operation_result));
            }
        }
    }
    double result;
    if (failure) {
        result = VALUE_OUT_OF_RANGE;
    } else {
        Element top = pop(&numbers);
        result = top.is_empty ? VALUE_OUT_OF_RANGE : top.value.number;
    }
    return result;
}

double execute(char operation, double a, double b) {
    double result = 0;
    switch (operation) {
        case OPERATOR_PLUS:
            result = a + b;
            break;
        case OPERATOR_MINUS:
            result = a - b;
            break;
        case OPERATOR_MUL:
            result = a * b;
            break;
        case OPERATOR_DIV:
            result = a / b;
            break;
        case OPERATOR_SIN:
            result = sin(a);
            break;
        case OPERATOR_COS:
            result = cos(a);
            break;
        case OPERATOR_LOG:
            result = log(a);
            break;
        case OPERATOR_TAN:
            result = tan(a);
            break;
        case OPERATOR_CTG:
            result = 1 / tan(a);
            break;
        case OPERATOR_SQRT:
            result = sqrt(a);
            break;
        default:
            break;  // do nothing
    }
    return result;
}
