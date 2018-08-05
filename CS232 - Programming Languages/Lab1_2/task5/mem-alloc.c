#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *ptr;
    /* allocate space to hold an int */
    ptr = (int *) malloc(sizeof(int));

    /* do stuff with the space */
    *ptr = 4;

    free(ptr);
    /* free up the allocated space */
}
