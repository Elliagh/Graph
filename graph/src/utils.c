#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#define BUFFER 64

int is_x(char c) { return c == 'x'; }

int is_digit(char c) { return (c >= '0' && c <= '9') || c == '.'; }

int is_unary_operator(char c) {
    return c == '~' || c == 'C' || c == 'S' || c == 'T' || c == 'G' || c == 'L' || c == 'Q';
}

char *allocate_string(int multiplier) { return malloc(multiplier * BUFFER * sizeof(char)); }

int need_more_space(int index, int multiplier) { return index == multiplier * BUFFER; }

char *expand_buffer(char *buffer, int index, int multiplier) {
    char *temp = allocate_string(multiplier);
    for (int i = 0; i < index; ++i) {
        temp[i] = buffer[i];
    }
    free(buffer);
    return temp;
}

char *read_string(void) {
    int multiplier = 1;
    int index = 0;
    char c;
    char *buffer = allocate_string(multiplier);
    while (1 == scanf("%c", &c) && c != '\n') {
        buffer[index] = c;
        index++;

        if (need_more_space(index, multiplier)) {
            multiplier *= 2;
            buffer = expand_buffer(buffer, index, multiplier);
        }
    }
    buffer[index] = '\0';
    return buffer;
}

void move_cursor(int row, int col) {
    // Use ANSI Escape sequence (https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html)
    printf("\033[2J");
    printf("\033[%d;%df", row + 1, col + 1);
}
