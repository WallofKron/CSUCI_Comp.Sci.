//  scanner_ad_hoc.c
//  Created by Bieszczad, A.J. on 2/21/13.
//  Copyright (c) 2013 CSUCI. All rights reserved.
//

#include "scanner.h"

TOKEN *ungottenToken = NULL;

//
// return token to the input, so it can be analyzed again
//
void ungetToken(TOKEN **token){
    
   ungottenToken = *token;
   *token = NULL;
}

//
// clean up the token structure
//
void freeToken(TOKEN **token){
    
   if (*token == NULL)
      return;

   if ((*token)->strVal != NULL)
      free((*token)->strVal);

   free(*token);

   *token = NULL;
}

//
// check if a collected sequence of characters is a keyword
//
int isKeyword(TOKEN *token, char *str){
    
   if( strcmp( str, "repeat" ) == 0 )
      token->type = REPEAT;
   else if( strcmp( str, "print" ) == 0 )
      token->type = PRINT;
   else
      return 0;

   return 1;
}

//
// scan input for a token using the ad hoc method
//
TOKEN *scannerAdHoc(){
    
   // reuse any token returned to the input
   if (ungottenToken != NULL)
   {
      TOKEN *tok = ungottenToken;
      ungottenToken = NULL;
      return tok;
   }

   // temporary buffer for collecting characters
   char tempString[BUF_SIZE];

   // acquire space for the new token
   TOKEN *token = (TOKEN*) malloc(sizeof(TOKEN));
   token->type = INVALID_TOKEN; // assume that the toekn is invalid to start with
   token->strVal = NULL;

   // analyze the input character by character figuring out what kind of token they constitute
   char c;
   int i;
   while ((token->type == INVALID_TOKEN) && ((c = getchar()) != EOF )){
       
      switch (c) {
         case ' ': // skip whitespace
         case '\t':
         case '\n':
            break;
         case 'a'...'z': // c is a letter
            i = 0;
            do {
               tempString[i++] = c;
               c = getchar();
            } while( c >= 'a' && c <= 'z');
            tempString[i] = '\0';
            ungetc(c, stdin); // the last character read is not a letter, so return it to the input stream
            if (!isKeyword(token, tempString))
            {
               token->type = IDENTTOKEN;
               token->strVal = (char*)malloc(strlen(tempString) + 1);
               strcpy(token->strVal, tempString);
            }
            return token;
         case '0'...'9': // if c is a number
            i = 0;
            do {
               tempString[i++] = c;
               c = getchar();
            } while( c >= '0' && c <= '9');
            tempString[i] = '\0';
            ungetc(c, stdin);
            token->type = NUMBERTOKEN;
            // this scanner saves each token as a string and
            // assumes that the parser will interpret it as needed
            token->strVal = (char *)malloc(strlen(tempString) + 1);
            strcpy(token->strVal, tempString);
            return token;
         default:
            // save the single character so the parser may distinguish operators if needed
            token->strVal = malloc(sizeof(char));
            token->strVal[0] = c;
            switch(c) {
               case '=':
                  token->type = ASSIGNMENT;
                  break;
               case ';':
                  token->type = SEMICOLON;
                  break;
               case '(':
                  token->type = LPAREN;
                  break;
               case ')':
                  token->type = RPAREN;
                  break;
               case '+':
                  token->type = PLUS;
                  break;
               case '-':
                  token->type = MINUS;
                  break;
               case '*':
                  token->type = MULT;
                  break;
               case '/':
                  token->type = DIV;
                  break;
               case '%':
                  token->type = MOD;
                  break;
            }
            return token;
      }
   }
   if (c == EOF){
       
      free(token);
      return NULL;
   }
   return token;
}

