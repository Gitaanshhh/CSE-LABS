/*
FLEX (Fast LEXical analyzer generator) is a tool for generating tokens. Instead of writing a lexical analyzer
from scratch, you only need to identify the vocabulary of a certain language, write a specification of patterns
using regular expressions (e.g. DIGIT [0-9]), and FLEX will construct a lexical analyzer for you.

The structure of Flex program has three sections as follows:
%{ definitions%}
%%
rules
%%
user subroutines

*/


%{ 
#include<stdio.h>
%}
%%
[a-zA-Z_][a-zA-Z0-9_]* { printf(" Identifier"); }
%%
int yywrap() { 
    return 1;
}
int main() {
    char stat[20];
    printf("Enter the valid C statement");
    scanf("%s",stat);
    yylex();
    return 0;
}