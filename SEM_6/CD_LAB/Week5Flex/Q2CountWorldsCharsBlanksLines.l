/*
2. Count the number of words, characters, blanks and lines in a given text.*/

%{
#include <stdio.h>

int words = 0;
int chars = 0;
int blanks = 0;
int lines = 0;
%}

%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
" "                 { blanks++; }
\n                  { chars++; lines++; }
.                   { chars++; }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("\nLines  : %d", lines);
    printf("\nWords  : %d", words);
    printf("\nBlanks : %d", blanks);
    printf("\nChars  : %d\n", chars);

    return 0;
}
