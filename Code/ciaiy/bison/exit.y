%{
#include <stdio.h>
#include <stdlib.h>

int     yylex(void);
void    yyerror(char *);

%}

%token EXIT

%%

exit:
    EXIT {printf("exit");}
    |
    ;

%%


void yyerror(char *s)
{
    printf("Error: %s n", s);
}

int main(void)
{
    yyparse();

    return 0;
}