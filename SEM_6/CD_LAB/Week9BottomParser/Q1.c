/*
1. Develop an SLR(1) Parser for the Given Expression Grammar and Demonstrate Parsing
Actions
E -> E+T|T
T -> T*F|F
F -> (E)|id

Accepted Strings : 

*/

#include <stdio.h>
#include <string.h>

char stack[50];
char input[50];
int top = -1;
int i = 0;

void push(char c) {
    stack[++top] = c;
}

void pop(int n) {
    top -= n;
}

void printStack() {
    for (int j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void printInput() {
    for (int j = i; j < strlen(input); j++)
        printf("%c", input[j]);
}

int checkReduce() {
    // F → id
    if (top >= 1 && stack[top] == 'd' && stack[top-1] == 'i') {
        pop(2);
        push('F');
        printf("\nReduce: F → id");
        return 1;
    }

    // T → F
    if (top >= 0 && stack[top] == 'F') {
        pop(1);
        push('T');
        printf("\nReduce: T → F");
        return 1;
    }

    // E → T
    if (top >= 0 && stack[top] == 'T') {
        pop(1);
        push('E');
        printf("\nReduce: E → T");
        return 1;
    }

    // T → T * F
    if (top >= 2 && stack[top] == 'F' && stack[top-1] == '*' && stack[top-2] == 'T') {
        pop(3);
        push('T');
        printf("\nReduce: T → T * F");
        return 1;
    }

    // E → E + T
    if (top >= 2 && stack[top] == 'T' && stack[top-1] == '+' && stack[top-2] == 'E') {
        pop(3);
        push('E');
        printf("\nReduce: E → E + T");
        return 1;
    }

    // F → (E)
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        pop(3);
        push('F');
        printf("\nReduce: F → (E)");
        return 1;
    }

    return 0;
}

int main() {
    strcpy(input, "id+id*id$");

    printf("Stack\tInput\tAction\n");

    while (1) {
        printStack();
        printf("\t");
        printInput();

        if (input[i] != '\0') {
            printf("\tShift %c", input[i]);
            push(input[i]);
            i++;
        }

        while (checkReduce());

        printf("\n");

        if (stack[top] == 'E' && input[i] == '$') {
            printf("\n✔ ACCEPTED\n");
            break;
        }

        if (i >= strlen(input))
            break;
    }

    return 0;
}