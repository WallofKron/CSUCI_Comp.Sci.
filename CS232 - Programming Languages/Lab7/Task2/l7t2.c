//Robert Florence
//CS 232
//Professor AJ
//3-14-16
//LAB7
//task2


#include "l7t2.h"

extern FILE *yyin; /* needed if using yyin in here */
extern int yylval;

char *keyword[NUM_OF_WORDS] = {"If","Then","While","Do","Plus","Minus","Mult","Div","Mod","SemiColon","Equals","Rparen","Lparen","Print","ID","NUM"};

int main(int argc, char *argv[]) {
    
    yyin = freopen(argv[1], "r", stdin);
    
    TOKEN tok = NO_TOK;
    
    while ((tok = yylex()) != 0){
        
        if ((tok == ID) || (tok == NUM)) {
            printf("<%s> value: %s\n", keyword[tok - IF], yyin->_bf._base);
        }
        
        else{
        printf("<%s>\n", keyword[tok - IF]);
        }
    }
    fclose(yyin);
    return 0;
}