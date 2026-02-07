/*
1. Count the number of vowels and consonants in the given input.
*/

%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;
%}

%%
[AEIOUaeiou]        { vowels++; }
[a-zA-Z]            { consonants++; }
.|\n                { /* ignore other characters */ }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("\nNumber of vowels: %d", vowels);
    printf("\nNumber of consonants: %d\n", consonants);

    return 0;
}
