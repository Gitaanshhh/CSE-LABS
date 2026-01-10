/*
Q1 That takes a file as input and replaces blank spaces and tabs by single space and writes the output to a
file.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fileA, *fileB;
    int ch;

    // Tracking consecutive spaces/tabs
    int spaceFlag = 0;   

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

        if (ch == ' ' || ch == '\t') {
            if (spaceFlag == 0) {
                putc(' ', fileB); 
                spaceFlag = 1;
            }
        } 
        else {
            putc(ch, fileB);
            spaceFlag = 0;
        }
    }

    fclose(fileA);
    fclose(fileB);

    printf("File processed successfully.\n");
    return 0;
}
