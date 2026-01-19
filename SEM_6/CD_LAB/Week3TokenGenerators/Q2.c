/*
2. Design a lexical analyzer that includes a getNextToken() function for processing a simple C program.
The analyzer should construct a token structure containing the row number, column number, and token
type for each identified token. The getNextToken() function must ignore tokens located within single-
line or multi-line comments, as well as those found inside string literals. Additionally, it should strip
out preprocessor directives.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

typedef enum {
    KEYWORD, IDENTIFIER, NUMBER,
    OPERATOR, SPECIAL, END
} TokenType;

typedef struct {
    int row, col;
    TokenType type;
    char lexeme[MAX];
} Token;

char *keywords[] = {
    "int","float","char","if","else",
    "while","for","return","void","main"
};

int isKeyword(char *s) {
    for (int i = 0; i < 10; i++)
        if (!strcmp(s, keywords[i]))
            return 1;
    return 0;
}

Token getNextToken(FILE *fp) {
    static int row = 1, col = 0;
    Token t;
    char ch, next;
    int i;

    while ((ch = fgetc(fp)) != EOF) {
        col++;

        if (ch == '\n') {
            row++; col = 0;
            continue;
        }

        if (isspace(ch)) continue;

        if (ch == '#') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            row++; col = 0;
            continue;
        }

        if (ch == '/') {
            next = fgetc(fp);
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                row++; col = 0;
                continue;
            }
            if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '\n') {
                        row++; col = 0;
                    }
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                continue;
            }
            ungetc(next, fp);
        }

        if (ch == '"') {
            while ((ch = fgetc(fp)) != '"' && ch != EOF)
                if (ch == '\n') {
                    row++; col = 0;
                }
            continue;
        }

        t.row = row;
        t.col = col;

        if (isalpha(ch) || ch == '_') {
            i = 0;
            t.lexeme[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                t.lexeme[i++] = ch;
                col++;
            }
            t.lexeme[i] = '\0';
            ungetc(ch, fp);

            t.type = isKeyword(t.lexeme) ? KEYWORD : IDENTIFIER;
            return t;
        }

        if (isdigit(ch)) {
            i = 0;
            t.lexeme[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                t.lexeme[i++] = ch;
                col++;
            }
            t.lexeme[i] = '\0';
            ungetc(ch, fp);

            t.type = NUMBER;
            return t;
        }

        if (strchr("+-*/=<>&|!", ch)) {
            t.lexeme[0] = ch;
            t.lexeme[1] = '\0';
            t.type = OPERATOR;
            return t;
        }

        if (strchr(";(),{}[]", ch)) {
            t.lexeme[0] = ch;
            t.lexeme[1] = '\0';
            t.type = SPECIAL;
            return t;
        }
    }

    t.type = END;
    return t;
}

int main() {
    FILE *fp = fopen("test.c", "r");
    if (!fp) {
        printf("File not found\n");
        return 1;
    }

    Token t;
    int prevRow = -1;

    while ((t = getNextToken(fp)).type != END) {

        if (t.row != prevRow) {
            if (prevRow != -1) printf("\n");
            printf("Row %d: ", t.row);
            prevRow = t.row;
        }

        printf("<%d,%d,", t.row, t.col);

        if (t.type == IDENTIFIER)
            printf("id");
        else if (t.type == NUMBER)
            printf("num");
        else
            printf("%s", t.lexeme);

        printf("> ");
    }

    printf("\n");
    fclose(fp);
    return 0;
}
