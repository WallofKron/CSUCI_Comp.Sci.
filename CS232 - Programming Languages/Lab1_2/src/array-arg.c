#include <stdio.h>

void init_array(int array[], int size) ;

int main(void) {
  int list[5];

  init_array(list, 5);
  int i;
  for (i = 0; i < 5; i++) 
    printf("next: %d\n", list[i]);
}

void init_array(int array[], int size) { /* why size ? */
		 /* arrays ALWAYS passed by reference */
 int i;
 for (i = 0; i < size; i++) 
    array[i] = 0;  
}
