/*
5. That changes a number from decimal to hexadecimal notation.
*/

%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+   {
            int num = atoi(yytext);
            printf("%X", num);   /* Convert to hexadecimal */
         }

.|\n     { printf("%s", yytext); }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter input:\n");
    yylex();
    return 0;
}
