/*
 Robert Florence
 Project - task1/2
 Prof. Bieszczad
 CSUCI
 3-18-16
 
 */



#include "l8t3.h"

int main(void)
{
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

// find out which function it is
int resolveFunc(char *func)
{
    char *funcs[] = { "neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min", "cbrt", "exp2", "hypot"};
    
    int i = 0;
    while (funcs[i][0] !='\0')
    {
        if (!strcmp(funcs[i], func))
            return i;
        
        i++;
    }
    yyerror("invalid function"); // paranoic -- should never happen
    return -1;
}

AST_NODE *symbol(char *symName)
{
    AST_NODE *p;
    size_t nodeSize;
    
    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    
    p->data.symbol.name = symName;
    
    return p;
}


// create a node for a number
AST_NODE *number(double value)
{
    AST_NODE *p;
    size_t nodeSize;
    
    // allocate space for the fixed size and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    
    p->type = NUM_TYPE;
    p->data.number.value = value;
    
    return p;
}

// create a node for a function
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
    AST_NODE *p;
    size_t nodeSize;
    
    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL){
        yyerror("out of memory");
    }
    
    p->type = FUNC_TYPE;
    p->data.function.name = funcName;
    p->data.function.op1 = op1;
    p->data.function.op2 = op2;
    
    return p;
}

// free a node
void freeNode(AST_NODE *p)
{
    if (!p){
        return;
    }
    
    if (p->type == FUNC_TYPE)
    {
        free(p->data.function.name);
        freeNode(p->data.function.op1);
        freeNode(p->data.function.op2);
    }
    
    free (p);
}

double evaluate(AST_NODE *p)
{
    if (!p){
        return 0;
    }
    
    if (p->type == 0) {
        return p->data.number.value;
    }
    char *func = p->data.function.name;
    
    int functnum = resolveFunc(func);
    
    
    AST_NODE *op1 = p->data.function.op1;
    AST_NODE *op2 = 0;
    
    if ((resolveFunc(func) >= 4 && (resolveFunc(func) <= 12)) || (resolveFunc(func) == 15)){
        op2 = p->data.function.op2;
    }
    
    switch(functnum){
            
        case 0:                    //  ------    case    --------
            return -evaluate(op1);
            break;
            
        case 1:                    //  ------    case    --------
            return (fabs(evaluate(op1)));
            break;
            
        case 2:                    //  ------    case    --------
            return (exp(evaluate(op1)));
            break;
            
        case 3:                    //  ------    case    --------
            if (op1->data.number.value < 0) {
                
                printf("ERROR: Cannot sqrt a Negative Number");
                return 0;
                
            } else {
                return (sqrt(evaluate(op1)));
            }
            break;
            
        case 4:                    //  ------    case    --------
            return (evaluate(op1) + evaluate(op2));
            break;
            
        case 5:                     //  ------    case    -------
            return (evaluate(op1) - evaluate(op2));
            break;
            
        case 6:                    //  ------    case    --------
            return (evaluate(op1) * evaluate(op2));
            break;
            
        case 7:                    //  ------    case    --------
            if(op2->data.number.value != 0){
                
                return (evaluate(op1) / evaluate(op2));
                
            }else{
                printf("ERROR: Cannot Divide By Zero!");
                return 0;
            }
            break;
            
        case 8:                    //  ------    case    --------
            return (fmod(evaluate(op1), evaluate(op2)));
            
            break;
            
        case 9:                    //  ------    case    --------
            return (log(evaluate(op2))/(log(evaluate(op1))));
            
            break;
            
        case 10:                    //  ------    case    --------
            return (pow(evaluate(op1),evaluate(op2)));
            
            break;
            
        case 11:                    //  ------    case    --------
            if (op1->data.number.value < op2->data.number.value) {
                
                return evaluate(op2);
                
            } else {
                return evaluate(op1);
            }
            break;
            
        case 12:                    //  ------    case    --------
            if (op1->data.number.value > op2->data.number.value) {
                
                return evaluate(op2);
                
            }else{
                return evaluate(op1);
            }
            break;
            
        case 13:                    //  ------    case    --------
            return (cbrt(evaluate(op1)));
            
            break;
            
        case 14:                    //  ------    case    --------
            return (pow(2,evaluate(op1)));
            
            break;
            
        case 15:                    //  ------    case    --------
            return (hypot(evaluate(op1), evaluate(op2)));
            
            break;
            
        default:
            printf("ERROR");
            break;
    }
    return 0;
}