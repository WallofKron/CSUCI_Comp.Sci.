//Robert Florence
//CS 232
//Professor AJ
//3-14-16
//LAB7
//task2


#ifndef l7t2_h_
#define l7t2_h_

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_WORDS 16

typedef enum {NO_TOK=0, IF=258, THEN, WHILE, DO, PLUSOP, MINUSOP, MULTOP, DIVOP, MODOP, SEMICOLON, EQUAL, LPAREN, RPAREN, PRINT, ID, NUM} TOKEN;


int yylex(void);


#endif