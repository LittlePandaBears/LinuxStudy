%{

#include <stdio.h>
#include <stdlib.h>

int     yylex(void);
void    yyerror(char *);

%}

 /* 上面%{ %}的代码和Lex一样，一般称为定义段。就是一些头文件声明，
  * 宏定义、变量定义声明、函数声明之类的。
  */

%token  INTEGER
%token  EXIT
%left   '+' '-'
%left   '*' '/'

%%

program:
       program expr exit 
       |
       ;

expr:
    INTEGER { $$ = $1; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    ;

exit :
    EXIT    {printf("exit"); $$ = $1;} 
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