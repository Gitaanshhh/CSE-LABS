/*
Q3 That takes C program as input, recognizes all the keywords and prints them in upper case.
*/

#include <stdio.h> //fopen(), fclose(), getc(), putc(), printf(), EOF
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //isalpha() → check letters, toupper()

const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof",
    "static","struct","switch","typedef","union","unsigned",
    "void","volatile","while"
};

int isKeyword(char *word) {
    int i;
    for (i = 0; i < 32; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void toUpperCase(char *word) {
    int i;
    for (i = 0; word[i]; i++)
        word[i] = toupper(word[i]);
}

int main() {
    FILE *fileA, *fileB;
    int ch, i = 0;
    char word[50];

    int inString = 0, inChar = 0;
    int startOfLine = 1;

    fileA = fopen("Input.c", "r");
    if (fileA == NULL) {
        printf("Cannot open input file\n");
        exit(0);
    }

    fileB = fopen("Out.c", "w");
    if (fileB == NULL) {
        printf("Cannot open output file\n");
        fclose(fileA);
        exit(0);
    }

    while ((ch = getc(fileA)) != EOF) {

        // Skip preprocessor directives
        if (startOfLine && ch == '#') {
            while (ch != '\n' && ch != EOF)
                ch = getc(fileA);
            startOfLine = 1;
            putc('\n', fileB);
            continue;
        }

        startOfLine = (ch == '\n');

        // string : ""
        if (ch == '"' && !inChar) {
            inString = !inString;
            putc(ch, fileB);
            continue;
        }

        // character : ''
        if (ch == '\'' && !inString) {
            inChar = !inChar;
            putc(ch, fileB);
            continue;
        }

        // Inside string or character
        if (inString || inChar) {
            putc(ch, fileB);
            continue;
        }

        if (isalpha(ch)) {
            word[i++] = ch;
        }
        else {
            if (i > 0) {
                word[i] = '\0';
                if (isKeyword(word))
                    toUpperCase(word);
                fputs(word, fileB);
                i = 0;
            }
            putc(ch, fileB);
        }
    }

    fclose(fileA);
    fclose(fileB);

    printf("Keywords converted to uppercase successfully.\n");
    return 0;
}
