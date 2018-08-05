//
//  parser.c
//  Created by Robert Florence on 3/3/16
//
#include "parser.h"


AST_NODE *program(){
    
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = PROGRAM;
    
   // printf("program\n");
    
    node->left_node = statement();
    if (node->left_node != NULL){
        node->right_node = program();
    }
    return node;
}

AST_NODE *statement(){
    
    TOKEN *readtkn;
    
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = STATEMENT;
    
    readtkn = scannerAdHoc();
    
    printf("statement: ");
    
    switch (readtkn->type) {
        case 2:
            node->left_node = assignStmt(readtkn);
            break;
            
        case 12:
            node->left_node = repeatStmt(readtkn);
            break;
            
        case 13:
            node->left_node = printStmt(readtkn);
            break;
            
        default:
            error();
            break;
    }
    return node;
}

AST_NODE *assignStmt(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = ASSIGN_STMT;
    
    
    node->left_node = id(currToken);
    
    printf("Assign: %s to: ",node->left_node->data.identifier);
    currToken = scannerAdHoc();
    
    if (currToken->type == 3) {
        
        currToken = scannerAdHoc();
        node->right_node = expr(currToken);
        
    } else {
        
        error();
    }

    currToken = scannerAdHoc();
    if (currToken->type == 4) {
        
        return node;
    }
    else{
        error();
    }
    return node;
}

AST_NODE *repeatStmt(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = REPEAT_STMT;
    
    printf("Repeat ");
    
    currToken = scannerAdHoc();
    
    if (currToken->type == 5) {
        
        currToken = scannerAdHoc();
        node->left_node = expr(currToken);
        
        currToken = scannerAdHoc();
        if (currToken->type == 6) {
            
            node->right_node = statement();
            
        }
        
    } else {
        
        error();
        
    }
    return node;
}

AST_NODE *printStmt(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = PRINT_STMT;
    
    currToken = scannerAdHoc();
    printf("Print");
    expr(currToken);
    
    
    return node;
}

AST_NODE *expr(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = EXPR;
    
    //printf("expr\n");
    TOKEN *readtkn;
    readtkn = currToken;
    currToken = scannerAdHoc();
    
    if(currToken->type == 7 || currToken->type == 8){
        
        node->left_node = expr(readtkn);
        
        
        if(currToken->type == 7){
            node->data.addOp = '+';
        }
        
        if(currToken->type == 8){
            node->data.addOp = '-';
        }
        
        currToken = scannerAdHoc();
        node->right_node = term(currToken);
        
    } else {
        ungetToken(&currToken);
        node->left_node = term(readtkn);
        
    }
    return node;
}

AST_NODE *term(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = TERM;
    
    TOKEN *readtkn;
    
    //printf("term\n");
    
    readtkn = currToken;
    currToken = scannerAdHoc();
    
    
    
    if(currToken->type == 9 || currToken->type == 10){
        
        node->left_node = term(readtkn);
        
        
        if(currToken->type == 9){
            node->data.multOp = '*';
        }
        
        if(currToken->type == 10){
            node->data.multOp = '/';
        }
        
        currToken = scannerAdHoc();
        node->right_node = factor(currToken);
        
    }else{
                ungetToken(&currToken);
        node->left_node = factor(readtkn);
        
    }
return node;
}

AST_NODE *factor(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = FACTOR;
    
    //printf("factor\n");
    
    switch (currToken->type) {
        case 1:
            node->left_node = number(currToken);
            break;
            
        case 2:
            node->left_node = id(currToken);
            break;
            
        case 8:
            currToken = scannerAdHoc();
            node->left_node = factor(currToken);
            break;
            
        case 5:
            currToken = scannerAdHoc();
            node->left_node = expr(currToken);
            break;
            
        default:
            error();
            break;
    }
    
    
    return node;
}

AST_NODE *id(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = IDENTIFIER;
    
    //printf("ID:");
    
    strcpy(node->data.identifier,currToken->strVal);
    
    
    return node;
}

AST_NODE *number(TOKEN *currToken){
    AST_NODE *node = malloc(sizeof(AST_NODE));
    node->type = NUMBER;
    
    
    node->data.number = atoi(currToken->strVal);
    
    printf("%2.1f\n", node->data.number);
    
    return node;
}

void error(TOKEN *currToken){
    printf("Parser error in: ");
    
    switch (currToken->type) {
        case 1:
            printf("{NumberTOKEN<%s>}\t", currToken->strVal);
            break;
        case 2:
            printf("{IDTOKEN<%s>}\t", currToken->strVal);
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
            break;
    }
    
}