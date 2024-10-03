#ifndef UTILS_H
#define UTILS_H

int is_x(char c);
int is_digit(char c);
int is_unary_operator(char c);

char* read_string(void);
void move_cursor(int row, int col);
char* allocate_string(int multiplier);

#endif
