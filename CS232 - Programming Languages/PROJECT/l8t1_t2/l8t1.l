%option noyywrap

%{
    #include "l8t1.h"
%}

digit [0-9]
number {digit}+(\.{digit}+)?
func "neg"|"abs"|"exp"|"sqrt"|"add"|"sub"|"mult"|"div"|"remainder"|"log"|"pow"|"max"|"min"|"cbrt"|"exp2"|"hypot"

%%

{number} {
                yylval.dval = strtod(yytext, NULL);
                printf("lex: NUMBER dval = %lf\n", yylval.dval);
                return NUMBER;
            }
"quit"      { return QUIT; }

{func}      {
                yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
                strcpy(yylval.sval, yytext);
                printf("lex: FUNC sval = %s\n", yylval.sval);
                return FUNC;
            }
"("         { 
                printf("lex: LPAREN\n"); 
                return LPAREN;
            }
")"         { 
                printf("lex: RPAREN\n"); 
                return RPAREN;
            }
"\n"        {
                printf("lex: EOL\n"); 
                return EOL;
            }
[ \t]       ; 

.           // yyerror("lex: invalid character");

%%
