//Robert Florence
//CS 232
//Professor AJ
//3-14-16
//LAB7

#ifndef __l7t1_h_
#define __l7t1_h_

#include <stdio.h>

#define NUM_OF_WORDS 8
typedef enum {NO_TOK=0, BANK, DOLLAR, FINANC, BUDGET, FUND, STOCK, BOND, INVEST} WORD; // TODO: complete

int sum(int[], int);
// function computing a sum of all element of an array
// the second parameter is the size of the array

int yylex(void);

#endif