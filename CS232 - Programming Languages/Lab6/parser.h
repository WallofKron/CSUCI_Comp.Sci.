//
// parser declarations
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

typedef enum {IDENTIFIER = 1, NUMBER, EXPR, TERM, ASSIGN_STMT, REPEAT_STMT, PRINT_STMT, FACTOR, ADDOP, MULTOP, PROGRAM, STATEMENT} AST_NODE_TYPE;

typedef struct ast_node
{
	AST_NODE_TYPE type;
	union
	{
		char identifier[128];
		double number;
		char addOp;
		char multOp;
	}data;
	struct ast_node *left_node;
	struct ast_node *right_node;
}AST_NODE;

TOKEN *scannerAdHoc();
AST_NODE *program();
AST_NODE *statement();
AST_NODE *assignStmt(TOKEN *currToken);
AST_NODE *repeatStmt(TOKEN *currToken);
AST_NODE *printStmt(TOKEN *currToken);
AST_NODE *expr(TOKEN *currToken);
AST_NODE *term(TOKEN *currToken);
AST_NODE *factor(TOKEN *currToken);
AST_NODE *id(TOKEN *currToken);
AST_NODE *number(TOKEN *currToken);
void error();
