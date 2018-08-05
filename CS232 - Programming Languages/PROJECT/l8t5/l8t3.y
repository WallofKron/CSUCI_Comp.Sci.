/*
s-expressions calculator
 program ::= | program s_expr EOL
 s_expr ::= number | symbol | ( func s_expr ) | ( func s_expr s_expr ) | ( ( let let_list ) s_expr )
 let_list ::= let_elem | let_list let_elem
 let_elem ::= ( symbol s_expr )
 symbol ::= letter+
 letter ::= [a-zA-Z]
 func ::= neg|abs|exp|sqrt|add|sub|mult|div|remainder|log|pow|max|min|exp2|cbrt|hypot
 number ::= [+|-]?digit+[.number+]
 digit ::= [0-9]
 
*/

%{
#include "l8t3.h"
%}

%union
{
   double dval;
   char *sval;
   struct ast_node *astNode;
};

%token <sval> FUNC
%token <sval> SYMBOL
%token <dval> NUMBER
%token LPAREN RPAREN EOL QUIT LETTOKEN

%type <astNode> s_expr

%%

program:/* empty */ { 
                       printf("> ");
                    }
        | program s_expr EOL {
                              // printf("yacc: program expr\n"); 
                              printf("%lf", evaluate($2));
                              freeNode($2);
                              printf("\n> "); 
                           }
        ;

let_list:
        let_elem {

//printf("yacc: let elem");

        }

        | let_list let_elem {

//printf("yacc: let list-let elem");

        }

        ;

let_elem:

        LPAREN SYMBOL s_expr RPAREN{
           // printf("yacc: symbol-s_expr");
           
        }

        ;

s_expr:
        NUMBER { 
                  //printf("yacc: NUMBER%lf", $1); 
                  $$ = number($1); 
               }
        | SYMBOL {
    
                //printf("yacc: Symbol%s", $1);
                $$ = symbol($1);

                }
        | LPAREN FUNC s_expr RPAREN {
                                     // printf("yacc: LPAREN FUNC expr RPAREN\n"); 
                                     $$ = function($2, $3, 0);
                                     //printf("%s(%lf)", $2, $3);
                                  }
        | LPAREN FUNC s_expr s_expr RPAREN {
                                     // printf("LPAREN FUNC expr expr RPAREN\n"); 
                                          // $$ = calc($2, $3, $4); 
                                          $$ = function($2, $3, $4);
                                       }
        | LPAREN LPAREN LETTOKEN let_list RPAREN s_expr RPAREN {
        
        //printf("yacc: let let list");


                }
        | QUIT {
                  //printf("QUIT\n"); 
                  exit(0);
               }
        
        | error { 
                        printf("error\n"); 
                        printf("> ");
                    }

        ;
%%

