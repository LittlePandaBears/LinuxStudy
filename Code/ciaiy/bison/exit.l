%{
#include <stdio.h>
#include "exit.tab.h"
%}

%%
[exit]      { printf("%s", yytext);     return EXIT; }
%%

int yywrap(void) { 
    return 1;
}