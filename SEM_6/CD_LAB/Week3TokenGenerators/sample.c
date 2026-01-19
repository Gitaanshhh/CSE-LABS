/*
Write a program in ‘C’ to identify the arithmetic and relational operators from the given input ‘C’ file.

Algorithm: Identification of arithmetic and relational operators from the given input file.
Step 1: Open the input ‘C’ file.
Step 2: Check if the file exists. Display an error message if the file doesn’t exists.
Step 3: Read each character from the input file.
Step 4: If character read is ‘=’ add it to the buffer.
            a. If the next character is ‘=’ display it as relational operator.
            b. Otherwise, display it as assignment operator.
Step 5: Otherwise, check if the next character is ‘<’ or ‘>’ or ‘!’
            a. Add it to the buffer.
            b. If next character is ‘=’ display It as Less Than Equal (LTE), Greater Than Equal (GTE) or
            NotEqualsTo (NE).
            c. Otherwise, display it as Less Than (LT), Greater Than (GT).
        Else
Step 6: Repeat step 3, 4 and 5 until EOF is encountered.
Step 7: Stop.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char c, buf[10];
    FILE *fp = fopen("test.c", "r");
    c = fgetc(fp);
    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    while (c != EOF) {
        int i = 0;
        buf[0] = '\0';
        if (c == '=') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                printf("\n Relational operator : %s", buf);
            }
            else {
                buf[i] = '\0';
                printf("\n Assignment operator: %s", buf);
            }
        }
        else {
            if (c == '<' || c == '>' || c == '!') {
                buf[i++] = c;
                c = fgetc(fp);

                if (c == '=')
                    buf [i++] = c;

                buf[i] = '\0';
                printf("\n Relational operator : %s", buf);
            }
            else 
                buf[i] = '\0';
        }
        c = fgetc(fp);
    }
}