#include "geometry.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"
#include "utils.h"

void draw(char* postfix_expression) {
    move_cursor(0, 0);
    for (int i = 0; i < ROWS; ++i) {
        if (i > 0) {
            printf("\n");
        }
        for (int j = 0; j < COLS; ++j) {
            printf("%c", get_drawable_symbol(i, j, postfix_expression));
        }
    }
}

char get_drawable_symbol(int row, int col, char* postfix_expression) {
    double x1, y1, x2, y2;
    set_rectangle(row, col, &x1, &y1, &x2, &y2);

    int found = 0;
    const double step = (x2 - x1) / SLICE_NUMBER;

    double x = x1;
    for (int i = 0; i < SLICE_NUMBER && !found; ++i, x += step) {
        double y = calculate(postfix_expression, x);
        found = !isnan(y) && y >= y1 && y <= y2;
    }

    return found ? '*' : '.';
}

void set_rectangle(int row, int col, double* x1, double* y1, double* x2, double* y2) {
    if (row == FIRST_ROW) {
        if (col == FIRST_COL)
            set_rectangle_top_left(x1, y1, x2, y2);  // (1)
        else if (col == LAST_COL)
            set_rectangle_top_right(x1, y1, x2, y2);  // (7)
        else
            set_rectangle_top_border(col, x1, y1, x2, y2);  // (8)
    } else if (row == MIDDLE_ROW) {
        if (col == FIRST_COL)
            set_rectangle_middle_left(x1, y1, x2, y2);  // (2)
        else if (col == LAST_COL)
            set_rectangle_middle_right(x1, y1, x2, y2);  // (6)
        else
            set_rectangle_common_case(row, col, x1, y1, x2, y2);  // (9 for middle)
    } else if (row == LAST_ROW) {
        if (col == FIRST_COL)
            set_rectangle_bottom_left(x1, y1, x2, y2);  // (3)
        else if (col == LAST_COL)
            set_rectangle_bottom_right(x1, y1, x2, y2);  // (5)
        else
            set_rectangle_bottom_border(col, x1, y1, x2, y2);  // (4)
    } else {
        if (col == FIRST_COL)
            set_rectangle_left_border(row, x1, y1, x2, y2);
        else if (col == LAST_COL)
            set_rectangle_right_border(row, x1, y1, x2, y2);
        else
            set_rectangle_common_case(row, col, x1, y1, x2, y2);  // (9)
    }
}

void set_rectangle_top_left(double* x1, double* y1, double* x2, double* y2) {
    *x1 = 0;
    *x2 = 0.5 * STEP_COL;
    *y1 = -1;
    *y2 = -1 + STEP_ROW / 2;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, y2);
}

void set_rectangle_top_right(double* x1, double* y1, double* x2, double* y2) {
    *x1 = (LAST_COL - 1 + 0.5) * STEP_COL;
    *x2 = 4 * M_PI;
    *y1 = -1;
    *y2 = -1 + STEP_ROW / 2;
    adjust_top_left_borders(x1, y1);
    exclude_borders(NULL, y2);
}

void set_rectangle_bottom_left(double* x1, double* y1, double* x2, double* y2) {
    *x1 = 0;
    *x2 = STEP_COL / 2;
    *y1 = 1 - STEP_ROW / 2;
    *y2 = 1;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, NULL);
}

void set_rectangle_bottom_right(double* x1, double* y1, double* x2, double* y2) {
    *x1 = (LAST_COL - 1 + 0.5) * STEP_COL;
    *x2 = 4 * M_PI;
    *y1 = 1 - STEP_ROW / 2;
    *y2 = 1;
    adjust_top_left_borders(x1, y1);
    // No necessity to exclude borders
}

void set_rectangle_middle_left(double* x1, double* y1, double* x2, double* y2) {
    *x1 = 0;
    *x2 = STEP_COL / 2;
    *y1 = -STEP_ROW / 2;
    *y2 = STEP_ROW / 2;
    adjust_top_left_borders(NULL, y1);
    exclude_borders(x2, y2);
}

void set_rectangle_middle_right(double* x1, double* y1, double* x2, double* y2) {
    *x1 = (LAST_COL - 1 + 0.5) * STEP_COL;
    *x2 = 4 * M_PI;
    *y1 = -STEP_ROW / 2;
    *y2 = STEP_ROW / 2;
    adjust_top_left_borders(x1, y1);
    exclude_borders(NULL, y2);
}

void set_rectangle_top_border(int col, double* x1, double* y1, double* x2, double* y2) {
    *x1 = (0.5 + col - 1) * STEP_COL;
    *x2 = (0.5 + col) * STEP_COL;
    *y1 = -1;
    *y2 = -1 + STEP_ROW / 2;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, y2);
}

void set_rectangle_bottom_border(int col, double* x1, double* y1, double* x2, double* y2) {
    *x1 = (0.5 + col - 1) * STEP_COL;
    *x2 = (0.5 + col) * STEP_COL;
    *y1 = 1 - STEP_ROW / 2;
    *y2 = 1;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, NULL);
}

void set_rectangle_left_border(int row, double* x1, double* y1, double* x2, double* y2) {
    *x1 = 0;
    *x2 = STEP_COL / 2;
    *y1 = (0.5 + row - 13) * STEP_ROW;
    *y2 = (0.5 + row - 12) * STEP_ROW;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, y2);
}

void set_rectangle_right_border(int row, double* x1, double* y1, double* x2, double* y2) {
    *x1 = (LAST_COL - 1 + 0.5) * STEP_COL;
    *x2 = 4 * M_PI;
    *y1 = (0.5 + row - 13) * STEP_ROW;
    *y2 = (0.5 + row - 12) * STEP_ROW;
    adjust_top_left_borders(x1, y1);
    exclude_borders(NULL, y2);
}

void set_rectangle_common_case(int row, int col, double* x1, double* y1, double* x2, double* y2) {
    *x1 = (0.5 + col - 1) * STEP_COL;
    *x2 = (0.5 + col) * STEP_COL;
    *y1 = (0.5 + row - 13) * STEP_ROW;
    *y2 = (0.5 + row - 12) * STEP_ROW;
    adjust_top_left_borders(x1, y1);
    exclude_borders(x2, y2);
}

void adjust_top_left_borders(double* x1, double* y1) {
    if (x1 != NULL) {
        *x1 = *x1 + STEP_COL * ADJUST_BORDER_PERCENT / 100;
    }
    if (y1 != NULL) {
        *y1 = *y1 + STEP_ROW * ADJUST_BORDER_PERCENT / 100;
    }
}

void exclude_borders(double* x2, double* y2) {
    if (x2 != NULL) {
        *x2 = *x2 - STEP_COL * EXCLUDE_BORDER_PERCENT / 100;
    }
    if (y2 != NULL) {
        *y2 = *y2 - STEP_ROW * EXCLUDE_BORDER_PERCENT / 100;
    }
}
