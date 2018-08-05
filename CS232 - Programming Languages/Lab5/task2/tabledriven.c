//  scanner.c
//  Created by Robert Florence on 2/27/16.
//

#include "scanner.h"



TOKEN *ungottenToken = NULL;

void ungetToken(TOKEN **token){
    
    ungottenToken = *token;
    *token = NULL;
}


void freeToken(TOKEN **token){
    
    if (*token == NULL)
        return;
    
    if ((*token)->strVal != NULL)
        free((*token)->strVal);
    
    free(*token);
    
    *token = NULL;
}


int isKeyword(TOKEN *token, char *str){
    
    if( strcmp(str, "repeat" ) == 0 )
        token->type = REPEAT;
    else if( strcmp(str, "print" ) == 0 )
        token->type = PRINT;
    else
        return 0;
    
    return 1;
}


TOKEN *tablescanner(){
    
    if (ungottenToken != NULL)
    {
        TOKEN *tok = ungottenToken;
        ungottenToken = NULL;
        return tok;
    }
    
    char tempString[BUF_SIZE];
    
    char tmpchr;
    
    TOKEN *token = (TOKEN*) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN;
    token->strVal = NULL;
    
    int i;
    char c;
    int state = 1;
    while ((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF )){
        
        switch (state) {
            case 1:
                switch(c) {
                    case ' ':
                        break;
                        
                    case '\t':
                        break;
                        
                    case '\n':
                        break;
                        
                    case '=':
                        state = 12;
                        break;
                    case ';':
                        state = 11;
                        break;
                    case '(':
                        state = 6;
                        ungetc(c,stdin);
                        
                        break;
                    case ')':
                        state = 7;
                        ungetc(c,stdin);

                        break;
                    case '+':
                        state = 8;
                        break;
                    case '-':
                        state = 9;
                        break;
                    case '*':
                        state = 10;
                        break;
                    case '/':
                        state = 2;
                        break;
                    case '%':
                        state = 13;
                        break;
                    case '.':
                        state = 14;
                        break;
                    case '0'...'9':
                        state = 15;
                        ungetc(c,stdin);
                        break;
                    case 'a'...'z':
                        state = 16;
                        ungetc(c,stdin);
                        break;
                        
                }
                
                break;
                
            case 2:
                switch(c) {
                    case '/':
                        state = 3;
                        break;
                        
                    case '*':
                        state = 4;
                        break;
                        
                    default:
                        token->type = DIV;
                        break;
                        
                }
                break;
                
            case 3:
                switch(c) {
                    case '/n':
                        state = 1;
                        break;
                        
                    default:
                        break;
                        
                }
                
                break;
                
            case 4:
                switch(c) {
                    case '*':
                        state = 5;
                        break;
                        
                    default:
                        break;
                        
                }
                break;
                
            case 5:
                switch(c) {
                    case '/':
                        state = 1;
                        break;
                        
                    case '*':
                        state = 5;
                        
                    default:
                        state = 4;
                        break;
                        
                }
                break;
                
            case 6:
                token->type = LPAREN;
                break;
                
            case 7:
                token->type = RPAREN;
                break;
                
            case 8:
                token->type = PLUS;
                break;
                
            case 9:
                token->type = MINUS;
                break;
                
            case 10:
                token->type = MULT;
                break;
                
            case 11:
                token->type = SEMICOLON;
                break;
                
            case 12:
                token->type = ASSIGNMENT;
                break;
                
            case 13:
                token->type = MOD;
                break;
                
            case 14:
                switch(c) {
                    case '0'...'9':
                        state = 15;
                        break;
                        
                    default:
                        state = 14;
                        break;
                        
                }
                break;
                
            case 15:
                i = 0;
                do {
                    tempString[i++] = c;
                    c = getchar();
                } while( c >= '0' && c <= '9');
                
                tempString[i] = '\0';
                ungetc(c, stdin);
                token->type = NUMBERTOKEN;
                
                
                token->strVal = (char *)malloc(strlen(tempString) + 1);
                strcpy(token->strVal, tempString);
                return token;

                break;
                
            case 16:
                i = 0;
                do {
                    tempString[i++] = c;
                    c = getchar();
                } while( c >= 'a' && c <= 'z');
                
                tempString[i] = '\0';
                
                ungetc(c, stdin);
                
                if (!isKeyword(token, tempString))
                {
                    token->type = IDENTTOKEN;
                    token->strVal = (char*)malloc(strlen(tempString) + 1);
                    strcpy(token->strVal, tempString);
                }
                return token;
                break;
                
                
            default:
                break;
                
        }
    }
    if (c == EOF){
        
        free(token);
        return NULL;
    }
    return token;
}