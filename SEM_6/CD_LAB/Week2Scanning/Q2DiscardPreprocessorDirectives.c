/*
Q2 To discard preprocessor directives from the given input ‘C’ file.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fileA, *fileB;
    int ch;
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

        // If '#' at the beginning, skip
        if (startOfLine && ch == '#') {
            while (ch != '\n' && ch != EOF)
                ch = getc(fileA);
            startOfLine = 1;   // New line starts
        }
        else {
            putc(ch, fileB);

            // Check for new line
            if (ch == '\n')
                startOfLine = 1;
            else
                startOfLine = 0;
        }
    }

    fclose(fileA);
    fclose(fileB);

    printf("Preprocessor directives removed successfully.\n");
    return 0;
}
