/*
3. Find the number of positive integer, negative integer, positive floating positive number and negative
floating point number

((0\.[0-9]*[1-9][0-9]*)|([1-9][0-9]*\.[0-9]+))   { pos_float++; }
-((0\.[0-9]*[1-9][0-9]*)|([1-9][0-9]*\.[0-9]+))  { neg_float++; }

*/

%{
#include <stdio.h>

int pos_int = 0;
int neg_int = 0;
int pos_float = 0;
int neg_float = 0;
%}

%%
-([0-9][0-9]*)\.[0-9]+    { neg_float++; }
([0-9][0-9]*)\.[0-9]+     { pos_float++; }

-([1-9][0-9]*)            { neg_int++; }
[1-9][0-9]*               { pos_int++; }

[ \t\n]+                  { /* ignore whitespace */ }
.                          { /* ignore other characters */ }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("\nPositive Integers        : %d", pos_int);
    printf("\nNegative Integers        : %d", neg_int);
    printf("\nPositive Floating Numbers: %d", pos_float);
    printf("\nNegative Floating Numbers: %d\n", neg_float);

    return 0;
}
