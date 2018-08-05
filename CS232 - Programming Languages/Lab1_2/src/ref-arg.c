#include <stdio.h>

int sum(int *pa, int *pb); 
		/* function prototype at start of file */

int main(void){
   int a=4, b=5;
   int *ptr = &b;
   int total = sum(&a,ptr); /* call to the function */

printf("The sum of 4 and 5 is %d\n", total);
}

int sum(int *pa, int *pb){   /* the function itself 
				- arguments passed by reference */
	return (*pa+*pb);      /* return by value */
}
