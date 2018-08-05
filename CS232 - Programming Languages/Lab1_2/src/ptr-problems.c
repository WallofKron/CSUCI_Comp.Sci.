#include <stdio.h>

void dosomething(int *ptr);

main() {
	int *p;
	dosomething(p);
	printf("Result from dosomething: %d\n", *p);     /* will this work ? */
}

void dosomething(int *ptr){ /* passed and returned by reference */
  int temp=32+12;
	
  ptr = &(temp);
}

/* compiles correctly, but gives run-time error */
