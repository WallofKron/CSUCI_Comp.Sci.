#include "scanner.h"


int main(){
    
    TOKEN *readtkn;
    
    while((readtkn = dfascanner())){
                
        switch (readtkn->type) {
            case 1:
                printf("{NumberTOKEN<%s>}\t", readtkn->strVal);
                break;
            case 2:
                printf("{IDTOKEN<%s>}\t", readtkn->strVal);
                break;
            case 3:
                printf("{<ASSIGNMENT>}\t");
                break;
            case 4:
                printf("{<SEMICOLON>}\t");
                break;
            case 5:
                printf("{<LPAREN>}\t");
                break;
            case 6:
                printf("{<RPAREN>}\t");
                break;
            case 7:
                printf("{<PLUS>}\t");
                break;
            case 8:
                printf("{<MINUS>}\t");
                break;
            case 9:
                printf("{<MULT>}\t");
                break;
            case 10:
                printf("{<DIV>}\t");
                break;
            case 11:
                printf("{<MOD>}\t");
                break;
            case 12:
                printf("{<REPEAT>}\t");
                break;
            case 13:
                printf("{<PRINT>}\t");
                break;
            case 14:
                printf("{<ENDOFINPUT>}\t");
                break;
            case 0:
                
                break;
                
            default:
                printf("ERROR: %u", readtkn->type);
                break;
        }
    }
    return 0;
}