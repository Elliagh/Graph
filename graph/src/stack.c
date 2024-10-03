#include "stack.h"

Element get_char_element(char c) {
    Element el = {.is_empty = 0, .type = 'c', .value.symbol = c};
    return el;
}

Element get_double_element(double d) {
    Element el = {.is_empty = 0, .type = 'd', .value.number = d};
    return el;
}

Element get_empty_element(void) {
    Element el = {.is_empty = 1};
    return el;
}

void push(Stack **head, Element element) {
    Stack *temp = malloc(sizeof(Stack));
    if (temp == NULL) {
        return;
    }
    temp->element = element;
    temp->next = *head;
    *head = temp;
}

Element pop(Stack **head) {
    if (*head == NULL) {
        return get_empty_element();  // Incorrect input
    }

    Stack *temp = *head;
    Element res = temp->element;
    *head = (*head)->next;
    free(temp);
    return res;
}
