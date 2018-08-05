#ifndef __l8t3_h_
#define __l8t3_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "y.tab.h"

int yyparse(void);
int yylex(void);
void yyerror(char *);

typedef enum { NUM_TYPE, FUNC_TYPE, SYMBOL_TYPE } AST_NODE_TYPE;

typedef struct
{
    char *name;
    
} SYMBOL_NODE;


typedef struct
{
    double value;
    
} NUMBER_AST_NODE;

typedef struct
{
    char *name;
    struct ast_node *op1;
    struct ast_node *op2;
    
} FUNCTION_AST_NODE;

typedef struct ast_node
{
    AST_NODE_TYPE type;
    union
    {
        SYMBOL_NODE symbol;
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
        
    } data;
} AST_NODE;

AST_NODE *number(double value);
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2);
AST_NODE *symbol(char* symName);
void freeNode(AST_NODE *p);

double evaluate(AST_NODE *ast);

#endif