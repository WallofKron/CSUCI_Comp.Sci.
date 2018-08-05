/* % must be in the first column (no indentation) */
/* to avoid warnning about yywrap() if we do not need it */
%option noyywrap


%{ // must start in the first column
   #include "l7t1.h"
   int number_of_sum = 0;
   int sum_of_num = 0;
   int totDol = 0;
%} // must start in the first column




/* aliasses */

digit [0-9]
number {digit}*



/* matching rules */
%%

"bank" {return BANK;}
"dollar" {return DOLLAR;}
"financ" {return FINANC;}
"budget" {return BUDGET;}
"fund" {return FUND;}
"stock" {return STOCK;}
"bond" {return BOND;}
"invest" {return INVEST;}

\${number}  {totDol = 0; totDol += strtod(yytext+1, NULL); return totDol;}


%%
