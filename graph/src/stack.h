#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef union value {
    char symbol;
    double number;
} Value;

typedef struct element {
    Value value;
    char type;
    int is_empty;
} Element;

typedef struct stack {
    Element element;
    struct stack *next;
} Stack;

void push(Stack **head, Element value);
Element pop(Stack **head);

Element get_char_element(char c);
Element get_double_element(double d);
Element get_empty_element(void);

#endif
