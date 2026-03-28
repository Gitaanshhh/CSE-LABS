%{
#include "y.tab.h"
%}

%%

[0-9]+      { return NUM; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"^"         { return '^'; }
"n"         { return 'n'; }
\n          { return '\n'; }
[ \t]       ;   /* ignore whitespace */

.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}