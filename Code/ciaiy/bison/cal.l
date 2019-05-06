%{

#include<stdio.h>

void yyerror(char *); 

#include "cal.tab.h"

%}

%%

[0-9]+      { yylval = atoi(yytext);  return INTEGER; }
[-+*/n] { return *yytext; }
[ t]        { ;  /* 去除空格 */ }
[exit]    { printf("***%s", yytext); return EXIT;}
%%

int yywrap(void)
{
    return 1;
}