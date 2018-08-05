/*
 Robert Florence
 Prof. A.J/Dolan-Stern
 CS362
 Lab 5
 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define maxlist 100

int main(int argc, char *argv[]){
   
    int temp = 0;
    int i=0;
    int numarray[maxlist];

    double alpha = 1.1;
    
    
    while ((scanf("%d",&numarray[i])!= EOF)) {          //take piped input from input.txt
        i++;
    }
    
    
    
    fclose(stdin);
    
    if (!freopen("/dev/tty", "r", stdin)) {
        perror("/dev/tty");
        exit(1);
    }                                       //close pipe as Stdin, and reconnect stdin to keyboard
    
    
    
    double predictedValueArray[i];
    
    while(!(alpha <= 1.0 && alpha >= 0.0)){                 //verify alphas within range
        printf("Alpha Value(0.0 to 1.0): ");
        scanf("%lf",&alpha);
    
    }
    
    
    predictedValueArray[0] = numarray[0];               //assume first CPU burst is the first average
    
    
    for (int j = 0; j < (sizeof(numarray) / sizeof(int)); j++) {            //using formula
        
        predictedValueArray[j+1] = ((alpha * numarray[j+1]) + ((1 - alpha) * predictedValueArray[j]));
        
        printf("Tau%d - Predicted:  %f\n", j, predictedValueArray[j]);
    }
    
    return 0;
}
