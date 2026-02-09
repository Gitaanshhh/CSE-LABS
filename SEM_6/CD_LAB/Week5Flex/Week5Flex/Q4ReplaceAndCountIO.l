/*

*/

%{
#include <stdio.h>

int scanf_count = 0;
int printf_count = 0;
FILE *res;
%}

%%
"scanf"    {
              scanf_count++;
              fprintf(res, "READ");
           }

"printf"   {
              printf_count++;
              fprintf(res, "WRITE");
           }

.|\n       { fprintf(res, "%s", yytext); }
%%

int yywrap()
{
    return 1;
}

int main(int argc, char *argv[])
{
    /*
    if (argc != 2)
    {
        printf("Usage: %s <input_file.c>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    */
    yyin = fopen("test.c", "r");
    
    if (!yyin)
    {
        printf("Error opening file\n");
        return 1;
    }

    res = fopen("res.c", "w");

    yylex();

    fclose(yyin);
    fclose(res);

    printf("\nReplacement successful!");
    printf("\n\nNumber of scanf  : %d", scanf_count);
    printf("\nNumber of printf : %d\n", printf_count);
    return 0;
}
