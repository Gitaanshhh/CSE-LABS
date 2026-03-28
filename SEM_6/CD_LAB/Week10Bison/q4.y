%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

/* Tokens */
%token NUM

%%

input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | exp '\n'   { printf("Valid postfix expression\n"); }
    ;

exp:
      NUM
    | exp exp '+'   { }
    | exp exp '-'   { }
    | exp exp '*'   { }
    | exp exp '/'   { }
    | exp exp '^'   { }
    | exp 'n'       { }   /* unary negation */
    ;

%%

/* Error handling */
void yyerror(const char *s) {
    printf("Invalid postfix expression\n");
}

/* Main function */
int main() {
    printf("Enter postfix expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}