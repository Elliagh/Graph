#include "parsing.h"

#include "stack.h"
#include "utils.h"

int is_operand(char sym) {
    int ans = 0;
    if (is_digit(sym) || sym == 'x') ans = 1;
    return ans;
}

int valid_sym(char sym) {
    int ans = 0;
    if (is_operand(sym) || sym == '*' || sym == '+' || sym == '-' || sym == '/') {
        ans = 1;
    }
    return ans;
}

// checks multicharacter operators and assign a one letter code
char operation_check(const char *str, int position, size_t len, int *offset) {
    char res = 'e';
    *offset = 2;
    if (position + 4 < (int)len) {
        if (str[position] == 's' && str[position + 1] == 'i' && str[position + 2] == 'n') {
            res = 'S';
        } else if (str[position] == 'c' && str[position + 1] == 'o' && str[position + 2] == 's') {
            res = 'C';
        } else if (str[position] == 'c' && str[position + 1] == 't' && str[position + 2] == 'g') {
            res = 'G';
        } else if (str[position] == 't' && str[position + 1] == 'a' && str[position + 2] == 'n') {
            res = 'T';
        } else if (str[position] == 's' && str[position + 1] == 'q' && str[position + 2] == 'r' &&
                   str[position + 3] == 't') {
            res = 'Q';
            *offset = 3;
        } else if (str[position] == 'l' && str[position + 1] == 'n') {
            res = 'L';
            *offset = 1;
        } else {
            res = 'e';
        }
    }
    return res;
}

// gets operators precedence
int precedence(char operator) {
    int ans = -1;
    if (operator== '(')
        ans = 0;
    else if (operator== '+' || operator== '-')
        ans = 1;
    else if (operator== '*' || operator== '/')
        ans = 2;
    else if (operator== 'Q')
        ans = 3;
    else if (operator== 'C' || operator== 'S' || operator== 'T' || operator== 'G' || operator== 'L')
        ans = 4;
    else if (operator== '~')
        ans = 5;

    return ans;
}

// handle a input expresion from  "22.1+cos(-sin(202*x))" to "22.1 + C ( ~ S ( 202 * x ) )"
int validate_string(const char *str, char *infix) {
    int res = 1, index = 0, offset = 0, *ptr = &offset;
    int left = 0, right = 0;
    for (int i = 0; i < (int)strlen(str); i++) {
        char s = str[i];
        if ((i == 0 || (i > 0 && str[i - 1] == '(')) && s == '-') {
            infix[index++] = '~';
            infix[index++] = SEPARATOR;
        } else if (is_digit(s)) {
            infix[index++] = s;
            if ((i < (int)strlen(str) - 1) && (!is_digit(str[i + 1]))) {
                infix[index++] = SEPARATOR;
            }
        } else if (valid_sym(s)) {
            infix[index++] = s;
            infix[index++] = SEPARATOR;
        } else if (s == '('){
		left++;
	} else if (s == ')'){
		right++;
	} else if (s == SEPARATOR) {
            // Ignore spaces
        } else {
            char op = operation_check(str, i, strlen(str), ptr);
            if (op != 'e') {
                infix[index++] = op;
                infix[index++] = SEPARATOR;
                i += offset;
            } else {
                res = 0;
                break;
            }
        }
    }
    if (left != right) res = 0;
    return res;
}

//turns postfix to infix using Dijkstra's algorithm
void infix2postfix(char *in, char *out) {
    Stack *stantion = NULL;
    int index = 0;
    for (int i = 0; i < (int)strlen(in); i++) {
        char s = in[i];
        if (s == ')') {
            char op;
            while ((op = pop(&stantion).value.symbol) != '(') {
                out[index++] = op;
                out[index++] = SEPARATOR;
            }
            // pop(&stantion);
        } else if (is_operand(s)) {
            out[index++] = s;
            if ((i < (int)strlen(in) - 1) && (!is_digit(in[i + 1]))) {
                out[index++] = SEPARATOR;
            }
        } else if (s == SEPARATOR) {
            // Ignore spaces
        } else {
            while (s != '(' && stantion != NULL &&
                   (precedence(stantion->element.value.symbol) > precedence(s))) {
                out[index++] = pop(&stantion).value.symbol;
                out[index++] = SEPARATOR;
            }
            push(&stantion, get_char_element(s));
        }
    }
    while (stantion != NULL) {
        out[index++] = pop(&stantion).value.symbol;
        out[index++] = SEPARATOR;
    }
}
