/*
1. For given subset of grammar 7.1, design RD parser with appropriate error messages with expected
character and row and column number.

Program -> main() { declarations assign_stat }
declarations -> data-type identifier-list; declarations | 𝜖
data-type -> int | char
identifier-list -> id | id, identifier-list
assign-stat -> id=id; | id=num

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int curr = 0;
int row = 1, col = 1;
char str[1000];

void Program();
void Declarations();
void IdentifierList();
void dataType();
void AssignStat();

void error(char *expected) {
    printf("ERROR at row %d, col %d: expected %s but found '%c'\n",
           row, col, expected, str[curr]);
    exit(1);
}

void valid() {
    printf("SUCCESS: Input string is valid!\n");
    exit(0);
}

void advance() {
    if (str[curr] == '\n') {
        row++;
        col = 1;
    } else
        col++;
    curr++;
}

void skipWhitespace() {
    while (isspace(str[curr]))
        advance();
}

void match(char expected) {
    skipWhitespace();
    if (str[curr] == expected)
        advance();
    else {
        char exp[10];
        sprintf(exp, "'%c'", expected);
        error(exp);
    }
}

void matchKeyword(char *kw) {
    skipWhitespace();
    int len = strlen(kw);
    if (strncmp(&str[curr], kw, len) == 0) 
        for (int i = 0; i < len; i++)
            advance();
    else
        error(kw);
}

int isIdentifier() {
    skipWhitespace();
    return isalpha(str[curr]);
}

void matchIdentifier() {
    skipWhitespace();
    if (!isalpha(str[curr]))
        error("identifier");

    while (isalnum(str[curr]))
        advance();
}

void matchNumber() {
    skipWhitespace();
    if (!isdigit(str[curr]))
        error("number");

    while (isdigit(str[curr]))
        advance();
}

void Program() {
    matchKeyword("main");
    match('(');
    match(')');
    match('{');

    Declarations();
    AssignStat();

    match('}');
}

void Declarations() {
    skipWhitespace();

    if (strncmp(&str[curr], "int", 3) == 0 ||
        strncmp(&str[curr], "char", 4) == 0) {

        dataType();
        IdentifierList();
        match(';');
        Declarations();  // recursion
    }
    // else epsilon
}

void dataType() {
    skipWhitespace();

    if (strncmp(&str[curr], "int", 3) == 0)
        matchKeyword("int");
    else if (strncmp(&str[curr], "char", 4) == 0)
        matchKeyword("char");
    else
        error("int or char");
}

void IdentifierList() {
    matchIdentifier();

    skipWhitespace();
    if (str[curr] == ',') {
        match(',');
        IdentifierList();
    }
}

void AssignStat() {
    matchIdentifier();
    match('=');

    skipWhitespace();
    if (isalpha(str[curr])) {
        matchIdentifier();   // id = id;
        match(';');
    } else if (isdigit(str[curr]))
        matchNumber();       // id = num
    else
        error("identifier or number");
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Cannot open file!\n");
        return 1;
    }

    int i = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF && i < sizeof(str) - 2)
        str[i++] = ch;
    fclose(fp);

    str[i++] = '$';
    str[i] = '\0';

    Program();

    skipWhitespace();
    if (str[curr] == '$')
        valid();
    else
        error("end of input");

    return 0;
}