/*
 Robert Florence
 Project - task1/2
 Prof. Bieszczad
 CSUCI
 3-18-16
 
 */



#include "l8t1.h"

int main(void)
{
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

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
   yyerror("invalid function");
   return -1;
}

double calc(char *func, double op1, double op2){

    if (strncmp(func, "neg", strlen(func)) == 0) {
        
        op1 = (op1 * -1);
        return op1;
        
    }
    if (strncmp(func, "abs", strlen(func)) == 0) {
        
        if (op1 < 0) {
            
            op1 = (op1*-1);
            return op1;
        
        } else {
            
            return op1;
        
        }
        
    }
    if (strncmp(func, "exp", strlen(func)) == 0) {
    
        return (exp(op1));
    
        
    }
    if (strncmp(func, "sqrt", strlen(func)) == 0) {
        
        return (sqrt(op1));
        
        
    }
    if (strncmp(func, "add", strlen(func)) == 0) {
        
        op1 = (op1+op2);
        return op1;
        
    }
    if (strncmp(func, "sub", strlen(func)) == 0) {
        
        op1 = (op1-op2);
        return op1;
        
    }
    if (strncmp(func, "mult", strlen(func)) == 0) {
        
        op1 = (op1*op2);
        return op1;
        
    }
    if (strncmp(func, "div", strlen(func)) == 0) {
        
        if (op2 == 0) {
            printf("ERROR: Cannot divide by 0");
            op1 = 0;
            return op1;
            
        } else {
            op1 = (op1/op2);
            return op1;

        }
        
    }
    if (strncmp(func, "remainder", strlen(func)) == 0) {
        
        return (fmod(op1,op2));
    
    }
    if (strncmp(func, "log", strlen(func)) == 0) {
        
        if (op1 == 2 || op1 == 10) {
        
        return ((log(op2)) / (log(op1)));

        
        } else {
            printf("ERROR: LOG base can be 2 or 10");
            op1 = 0;
            return op1;
        }
        
    }
    if (strncmp(func, "pow", strlen(func)) == 0) {
        
        return (pow(op1,op2));
        
    }
    if (strncmp(func, "min", strlen(func)) == 0) {
        
        if (op1 < op2) {
        
            return op1;
        } else {
        
            return op2;
        }
        
    }
    if (strncmp(func, "max", strlen(func)) == 0) {
        
        if (op1 > op2) {
            
            return op1;
            
        } else {
            
            return op2;
        }
    }
    if (strncmp(func, "cbrt", strlen(func)) == 0) {
        
        return (cbrt(op1));
        
    }
    if (strncmp(func, "exp2", strlen(func)) == 0) {
        
        return (pow(2,op1));
        
    }
    if (strncmp(func, "hypot", strlen(func)) == 0) {
        
        return (hypot(op1,op2));
        
    }
    return 0.0;
}