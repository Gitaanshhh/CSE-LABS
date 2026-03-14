/*
Design the recursive descent parser to parse array declarations and expression statements with error reporting.
Subset of grammar 7.1 is as follows:

Program -> main() {declrations statement-list}
identifier-list -> id | id, identifier-list | id[number], identifier-list | id[number]
statement-list -> statement statement-list | 𝜖
statement -> assign-stat
assign-stat -> id = expn
expn -> simple-expn eprime
eprime -> relop simple-expn | 𝜖
simple-expn -> term seprim
seprime -> addop term seprime | 𝜖
term -> factor tprime 
tprime -> mulop factor tprime | 𝜖
factor -> id | num
relop -> == | != | <= | >= | > | <
addop -> + | -
mulop * | / | %

Accepted Strings : 
main(){a,b,c}
main(){a[5],b,c[10]}
main(){a=5}
main(){a,b,c}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int curr = 0;
char str[1000];  // buffer for the file contents

void Program();
void Declarations();
void IdentifierList();
void StatementList();
void Statement();
void AssignStat();
void Expn();
void Eprime();
void SimpleExpn();
void Seprime();
void Term();
void Tprime();
void Factor();
void Relop();
void Addop();
void Mulop();

void invalid() {
    printf("---------------ERROR!----------------\n");
    exit(0);
}

void valid() {
    printf("---------------SUCCESS!---------------\n");
    exit(0);
}

void match(char expected) {
    if (str[curr] == expected)
        curr++;
    else
        invalid();
}

void skipWhitespace() {
    while (isspace(str[curr]))
        curr++;
}

int isRelopStart() {
    char c = str[curr];
    return (c == '=' || c == '!' || c == '<' || c == '>');
}

int isAddop() {
    return (str[curr] == '+' || str[curr] == '-');
}

int isMulop() {
    return (str[curr] == '*' || str[curr] == '/' || str[curr] == '%');
}

void Program() {
    skipWhitespace();
    if (strncmp(&str[curr], "main", 4) == 0)
        curr += 4;
    else
        invalid();

    skipWhitespace();
    match('(');
    match(')');
    skipWhitespace();
    match('{');
    skipWhitespace();

    Declarations();
    skipWhitespace();
    StatementList();
    skipWhitespace();
    match('}');
}

void Declarations() {
    skipWhitespace();
    if (isalpha(str[curr]))
        IdentifierList();
}

void IdentifierList() {
    skipWhitespace();
    if (!isalpha(str[curr]))
        invalid();

    curr++; // consume id

    skipWhitespace();
    // array
    if (str[curr] == '[') {
        curr++;
        if (!isdigit(str[curr]))
            invalid();
        while (isdigit(str[curr]))
            curr++;
        match(']');
        skipWhitespace();
    }

    // optional assignment
    if (str[curr] == '=') {
        curr++;
        skipWhitespace();
        Expn();
        skipWhitespace();
    }

    // more identifiers
    if (str[curr] == ',') {
        curr++;
        IdentifierList();
    }
}

void StatementList() {
    skipWhitespace();
    if (isalpha(str[curr])) {
        Statement();
        StatementList();
    }
    // epsilon
}

void Statement() {
    skipWhitespace();
    AssignStat();
}

void AssignStat() {
    skipWhitespace();
    if (!isalpha(str[curr]))
        invalid();
    curr++; // id
    skipWhitespace();
    match('=');
    skipWhitespace();
    Expn();
}

void Expn() {
    skipWhitespace();
    SimpleExpn();
    Eprime();
}

void Eprime() {
    skipWhitespace();
    if (isRelopStart()) {
        Relop();
        skipWhitespace();
        SimpleExpn();
    }
}

void SimpleExpn() {
    skipWhitespace();
    Term();
    Seprime();
}

void Seprime() {
    skipWhitespace();
    if (isAddop()) {
        Addop();
        skipWhitespace();
        Term();
        Seprime();
    }
}

void Term() {
    skipWhitespace();
    Factor();
    Tprime();
}

void Tprime() {
    skipWhitespace();
    if (isMulop()) {
        Mulop();
        skipWhitespace();
        Factor();
        Tprime();
    }
}

void Factor() {
    skipWhitespace();
    if (isalpha(str[curr]))
        curr++;
    else if (isdigit(str[curr]))
        while (isdigit(str[curr]))
            curr++;
    else if (str[curr] == '(') {
        curr++;
        skipWhitespace();
        Expn();
        skipWhitespace();
        match(')');
    }
    else
        invalid();
}

void Relop() {
    if (str[curr] == '=' && str[curr+1] == '=')
        curr += 2;
    else if (str[curr] == '!' && str[curr+1] == '=')
        curr += 2;
    else if (str[curr] == '<' && str[curr+1] == '=')
        curr += 2;
    else if (str[curr] == '>' && str[curr+1] == '=')
        curr += 2;
    else if (str[curr] == '<' || str[curr] == '>')
        curr++;
    else
        invalid();
}

void Addop() {
    if (str[curr] == '+' || str[curr] == '-')
        curr++;
    else
        invalid();
}

void Mulop() {
    if (str[curr] == '*' || str[curr] == '/' || str[curr] == '%')
        curr++;
    else
        invalid();
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Cannot open file!\n");
        return 1;
    }

    // read file into str[]
    int i = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF && i < sizeof(str)-2) {
        str[i++] = ch;
    }
    fclose(fp);

    str[i++] = '$'; // end of input marker
    str[i] = '\0';

    Program();
    skipWhitespace();
    if (str[curr] == '$')
        valid();
    else
        invalid();
}