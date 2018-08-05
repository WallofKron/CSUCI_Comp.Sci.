#include <stdio.h>

#define NUM_OF_CELLS 12

int main(void)
{
    double number[NUM_OF_CELLS]; /* 12 cells, one cell per student */
    double input = 0.0;
    double sum = 0.0;
    int index = 0;
    
    /* Always initialize array before use */
    
    for (index = 0; index < NUM_OF_CELLS; index++) {
        
        scanf("%lf",&input);
        number[index] = input;
        
    }
    
    for (index = 0; index < NUM_OF_CELLS; index++) {
        
        sum += number[index];  /* sum array elements */
        
    }
    
    printf("Data: ");
    
    for (int i = 0; i < NUM_OF_CELLS; i++) {
        if(i == 11){
            
            printf("%.2f", number[i]);
            
        }else{
            printf("%.2f, ", number[i]);
        }
    }
    double average = 0;
    
    average = (sum / NUM_OF_CELLS);
    printf("\nAverage: %.2f\n", average);
    return 0;
}
