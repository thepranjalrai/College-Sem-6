%{
#include<stdio.h>            
%}

%%

[ /t] ;

[+|-|*|/|%|=|>|<] { printf("\n%s is an arithmetic operator",yytext); }

[@|#|$] { printf("\n%s is a special symbol",yytext); }

[,|;|{|}|(|)|"|"] { printf("\n%s is a separator",yytext); }

if |
for |
while |
goto |
do |
switch |
case |
break |
continue |
int |
char |
float |
double |
auto |
struct |
virtual |
void |
main |
include       { printf("\n%s is a keyword",yytext); }

 
[0-9]+  { printf("\n %s is a constant",yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("\n%s is an identifier",yytext); }


%%

int main()
{
yyin = fopen("input.txt", "r");
if(yyin == NULL)
{
printf("error opening the file");
}

yylex();
}

int yywrap()
{
return 0;
}