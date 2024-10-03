#ifndef CALC_H
#define CALC_H

double calculate(char* postfix_expression, double x);
double execute(char operation, double a, double b);
double apply_unary_operator(char c, double value, int* failure);
double parse_number(char* postfix_expression, int* i, int* failure);

#define VALUE_OUT_OF_RANGE -200
#define NUMBER_MAX_SYMBOLS 100

#endif
