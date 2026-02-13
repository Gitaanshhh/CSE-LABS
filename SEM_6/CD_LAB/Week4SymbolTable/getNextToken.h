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

    /*
    Imp Fns :
    isspace(ch)
    ch = fgetc(fp)
    ungetc(next, fp)
    isalpha(ch) || ch == '_'                //isalpha(ch) → allows a–z, A–Z
    isalnum(ch = fgetc(fp)) || ch == '_'    //isalnum() → letters + digits
    isdigit(ch)
    strchr("+-* /=<>&|!", ch                //returns ptr to first match else NULL
    !strcmp(s, keywords[i])                 //returns 0 on match
    */

    while ((ch = fgetc(fp)) != EOF) {
        col++;

        // New Line
        if (ch == '\n') {
            row++; col = 0;
            continue;
        }

        // Space
        if (isspace(ch)) continue;

        // Preprocessor directives
        if (ch == '#') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            row++; col = 0;
            continue;
        }

        // Comments
        if (ch == '/') {
            next = fgetc(fp);
            // Single line
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                row++; 
                col = 0;
                continue;
            }
            // Multiline
            if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '\n') {
                        row++; 
                        col = 0;
                    }
                    if (prev == '*' && ch == '/') 
                        break;
                    prev = ch;
                }
                continue;
            }
            ungetc(next, fp);
        }

        // Strings
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

            next = fgetc(fp);
            if ((next == '=' && strchr("+-*/%<>=!", ch)) ||
                (ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|')) {
                t.lexeme[1] = next;
                t.lexeme[2] = '\0';
                col++;
            } else {
                ungetc(next, fp);
            }

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