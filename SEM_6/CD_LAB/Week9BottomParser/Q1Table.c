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
#include <stdlib.h>

#define MAX 100

int stateStack[MAX];
char symbolStack[MAX];
int top = -1;

char input[MAX];
int ip = 0;

void push(int state, char symbol) {
    top++;
    stateStack[top] = state;
    symbolStack[top] = symbol;
}

void pop(int n) {
    top -= n;
}

int getState() {
    return stateStack[top];
}

void printStack() {
    for (int i = 0; i <= top; i++)
        printf("%c%d ", symbolStack[i], stateStack[i]);
}

char *ACTION[12][6] = {
    {"S5", "", "", "S4", "", ""},
    {"", "S6", "", "", "", "ACC"},
    {"", "R2", "S7", "", "R2", "R2"},
    {"", "R4", "R4", "", "R4", "R4"},
    {"S5", "", "", "S4", "", ""},
    {"", "R6", "R6", "", "R6", "R6"},
    {"S5", "", "", "S4", "", ""},
    {"S5", "", "", "S4", "", ""},
    {"", "S6", "", "", "S11", ""},
    {"", "R1", "S7", "", "R1", "R1"},
    {"", "R3", "R3", "", "R3", "R3"},
    {"", "R5", "R5", "", "R5", "R5"}
};

// GOTO table
// Columns: E=0, T=1, F=2
int GOTO[12][3] = {
    {1, 2, 3},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1},
    {8, 2, 3},
    {-1,-1,-1},
    {-1, 9, 3},
    {-1,-1,10},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1}
};

int getCol(char c) {
    if (c == 'i') return 0; // id
    if (c == '+') return 1;
    if (c == '*') return 2;
    if (c == '(') return 3;
    if (c == ')') return 4;
    if (c == '$') return 5;
    return -1;
}

// Production rules
char LHS[] = {' ', 'E','E','T','T','F','F'};
int RHS_len[] = {0,3,1,3,1,3,1};

void parse() {
    push(0, '$');

    printf("Stack\t\tInput\t\tAction\n");

    while (1) {
        int state = getState();
        char a = input[ip];

        int col = getCol(a);
        if (col == -1) {
            printf("\nInvalid symbol!\n");
            return;
        }

        char *action = ACTION[state][col];

        printStack();
        printf("\t\t%s\t\t%s\n", &input[ip], action);

        if (strcmp(action, "ACC") == 0) {
            printf("\n✔ STRING ACCEPTED\n");
            return;
        }

        if (action[0] == 'S') {
            int nextState = atoi(&action[1]);
            push(nextState, a);
            ip++;
        }

        else if (action[0] == 'R') {
            int rule = atoi(&action[1]);

            pop(RHS_len[rule]);

            int state2 = getState();
            char lhs = LHS[rule];

            int gotoCol;
            if (lhs == 'E') gotoCol = 0;
            else if (lhs == 'T') gotoCol = 1;
            else gotoCol = 2;

            int nextState = GOTO[state2][gotoCol];

            push(nextState, lhs);

            printf("Reduced using rule %d\n", rule);
        }
        else {
            printf("\n❌ ERROR: Invalid string\n");
            return;
        }
    }
}

int main() {
    printf("Enter input (use i for id, end with $): ");
    scanf("%s", input);

    parse();

    return 0;
}