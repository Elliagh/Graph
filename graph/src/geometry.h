#include <math.h>

#ifndef GEOMETRY_H
#define GEOMETRY_H

void draw(char* postfix_expression);

#define M_PI 3.14159265358979323846
#define ROWS 25
#define COLS 80

#define FIRST_ROW 0
#define LAST_ROW 24
#define FIRST_COL 0
#define LAST_COL 79

#define MIDDLE_ROW 12

#define STEP_COL ((double)4 * M_PI / 79)
#define STEP_ROW ((double)1 / 12)

#define SLICE_NUMBER 10
#define ADJUST_BORDER_PERCENT 0
#define EXCLUDE_BORDER_PERCENT 2

char get_drawable_symbol(int row, int col, char* postfix_expression);
void set_rectangle(int row, int col, double* x1, double* y1, double* x2, double* y2);

void set_rectangle_top_left(double* x1, double* y1, double* x2, double* y2);
void set_rectangle_top_right(double* x1, double* y1, double* x2, double* y2);
void set_rectangle_bottom_left(double* x1, double* y1, double* x2, double* y2);
void set_rectangle_bottom_right(double* x1, double* y1, double* x2, double* y2);

void set_rectangle_middle_left(double* x1, double* y1, double* x2, double* y2);
void set_rectangle_middle_right(double* x1, double* y1, double* x2, double* y2);

void set_rectangle_top_border(int col, double* x1, double* y1, double* x2, double* y2);
void set_rectangle_bottom_border(int col, double* x1, double* y1, double* x2, double* y2);
void set_rectangle_left_border(int row, double* x1, double* y1, double* x2, double* y2);
void set_rectangle_right_border(int row, double* x1, double* y1, double* x2, double* y2);
void set_rectangle_common_case(int row, int col, double* x1, double* y1, double* x2, double* y2);

void adjust_top_left_borders(double* x1, double* y1);
void exclude_borders(double* x2, double* y2);

#endif
