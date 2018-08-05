%option noyywrap

%{
#include "l7t2.h"
int totDol = 0;
int yylval = 0;
%}

digit [0-9]
number {digit}*

letter	[a-zA-Z]
word	({letter}[a-zA-Z0-9]+)

%%

"if" {return IF;}
"then" {return THEN;}
"while" {return WHILE;}
"do" {return DO;}
"+" {return PLUSOP;}
"-" {return MINUSOP;}
"*" {return MULTOP;}
"/" {return DIVOP;}
"%" {return MODOP;}
";" {return SEMICOLON;}
"=" {return EQUAL;}
"(" {return LPAREN;}
")" {return RPAREN;}
"print" {return PRINT;}

[ \t\n]+ 		;

{word} {return ID;}

{number}  {totDol = 0; totDol += strtod(yytext, NULL); yylval = totDol; return NUM;}

. return yytext[0];
%%
