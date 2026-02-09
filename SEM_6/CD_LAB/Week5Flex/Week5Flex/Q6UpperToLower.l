/*
6. Convert uppercase characters to lowercase characters of C file excluding the characters present in the
comment.
*/

%{
#include<stdio.h>
%}

%%
[a-z]  {printf("%c",yytext[0]); }
[A-Z] {printf("%c",yytext[0]+32); }
"//" {
    printf("%s", yytext); 
    char c;
    while ((c = input()) != '\n' && c != 0) {
        putchar(c);     
    }
    if (c == '\n') putchar('\n');
}
"/*" {
    printf("%s", yytext); 
    char c, prev = '\0';
    while ((c = input()) != '/' && c != 0 && prev != '*') {
        putchar(c);     
        prev = c;
    }
    putchar('/');
    if (c == '\n') putchar('\n');
}
.        { printf("%s", yytext); }
\n       { printf("%s", yytext); }
%%

int yywrap() { return 1; }

int main() {
    yyin = fopen("test.c", "r");
    
    if (!yyin) {
        printf("Error opening file\n");
        return 1;
    }

    yylex();

    fclose(yyin);
   
    printf("\nReplacement successful!");
    return 0;

}