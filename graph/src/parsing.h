#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>
#include <string.h>

#include "stack.h"
#define SEPARATOR ' '

#define OPERATOR_PLUS '+'
#define OPERATOR_MINUS '-'
#define OPERATOR_MUL '*'
#define OPERATOR_DIV '/'
#define OPERATOR_UNARY_MINUS '~'
#define OPERATOR_COS 'C'
#define OPERATOR_SIN 'S'
#define OPERATOR_TAN 'T'
#define OPERATOR_CTG 'G'
#define OPERATOR_LOG 'L'
#define OPERATOR_SQRT 'Q'

int precedence(char operand);
int validate_string(const char *str, char *infix);
char operation_check(const char *str, int position, size_t len, int *offset);
void infix2postfix(char *in, char *out);

#endif
