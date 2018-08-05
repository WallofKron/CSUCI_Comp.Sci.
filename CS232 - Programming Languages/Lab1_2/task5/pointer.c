#include <stdio.h>

int main(void) {
	int j;
	int *ptr;

	ptr=&j;   /* initialize ptr before using it */
		    /* *ptr=4 does NOT initialize ptr */

	*ptr=4;     /* j <- 4 */

	j=*ptr;     /* j <- ??? */
}
