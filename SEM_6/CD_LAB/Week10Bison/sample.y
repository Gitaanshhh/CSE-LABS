/*
Write a Bison program to check the syntax of a simple expression involving operators +, -, * and /.

bison -d sample.y 
flex sample.l 
gcc lex.yy.c sample.tab.c -o output

*/

%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex(void);
    int yyerror(char *msg);
%}

%token NUMBER ID NL
%left '+'
%left '*'

%%
stmt : exp NL { printf("Valid Expression"); exit(0);}
    ;
exp : exp '+' term
    | term
term: term '*' factor
    |factor
factor: ID
    | NUMBER
;
%%

int yywrap()
{
    return 1;
}

int yyerror(char *msg)
{
    printf("Invalid Expression\n");
    exit(0);
}
void main ()
{
    printf("Enter the expression\n");
    yyparse();
}