/*
1. Write functions to identify the following tokens.
a. Arithmetic, relational and logical operators.
b. Special symbols, keywords, numerical constants, string literals and identifiers.

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isKeyword(char *str);
void identifyOperator(char ch, FILE *fp);
void identifyToken(char ch, FILE *fp);

char *keywords[] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void", "main"
};

int main() {
    FILE *fp;
    char ch;

    fp = fopen("test.c", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch))
            continue;

        if (isalpha(ch) || ch == '_')
            identifyToken(ch, fp);
        else if (isdigit(ch))
            identifyToken(ch, fp);
        else if (ch == '"' )
            identifyToken(ch, fp);
        else
            identifyOperator(ch, fp);
    }

    fclose(fp);
    return 0;
}

void identifyToken(char ch, FILE *fp) {
    char buf[50];
    int i = 0;

    //isaplha -> checks whether the char is an alphabet
    if (isalpha(ch) || ch == '_') {
        buf[i++] = ch;
        //isalnum -> checks whether the char is an alphanumeric (alphabet or number) 
        while (isalnum(ch = fgetc(fp)) || ch == '_')
            buf[i++] = ch;

        buf[i] = '\0';
        //ungetc -> Pushes a char back into the input stream so it can be read again
        ungetc(ch, fp);

        if (isKeyword(buf))
            printf("\n Keyword            : %s", buf);
        else
            printf("\n Identifier         : %s", buf);
    }

    else if (isdigit(ch)) {
        buf[i++] = ch;
        while (isdigit(ch = fgetc(fp)))
            buf[i++] = ch;

        buf[i] = '\0';
        ungetc(ch, fp);
        printf("\n Numeric Constant   : %s", buf);
    }

    else if (ch == '"') {
        buf[i++] = ch;
        while ((ch = fgetc(fp)) != '"')
            buf[i++] = ch;
        buf[i++] = '"';
        buf[i] = '\0';

        printf("\n String Literal     : %s", buf);
    }
}

void identifyOperator(char ch, FILE *fp) {
    char next;

    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
        printf("\n Arithmetic Operator: %c", ch);

    else if (ch == '<' || ch == '>' || ch == '=' || ch == '!') {
        next = fgetc(fp);
        if (next == '=')
            printf("\n Relational Operator: %c%c", ch, next);
        else {
            ungetc(next, fp);
            if (ch == '=')
                printf("\n Assignment Operator: %c", ch);
            else
                printf("\n Relational Operator: %c", ch);
        }
    }

    else if (ch == '&' || ch == '|') {
        next = fgetc(fp);
        if (ch == next)
            printf("\n Logical Operator   : %c%c", ch, next);
        else
            ungetc(next, fp);
    }

    else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
             ch == '{' || ch == '}' || ch == '[' || ch == ']')
        printf("\n Special Symbol     : %c", ch);
}

int isKeyword(char *str) {
    int i;
    for (i = 0; i < 10; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    return 0;
}
