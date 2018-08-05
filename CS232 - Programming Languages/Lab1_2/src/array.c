#include <stdio.h>

#define NUM_OF_CELLS 12

int main(void) 
{
    int number[NUM_OF_CELLS]; /* 12 cells, one cell per student */
    int index, sum = 0;
		/* Always initialize array before use */
    for (index = 0; index < NUM_OF_CELLS; index++) {
	number[index] = index; 
    }
    /* now, number[index]=index; will cause error:why ?*/

    for (index = 0; index < NUM_OF_CELLS; index = index + 1) {
	sum += number[index];  /* sum array elements */
    }
	
    return 0;
}
