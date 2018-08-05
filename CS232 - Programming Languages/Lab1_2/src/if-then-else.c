#include <stdio.h>
#define DANGERLEVEL 5    /* C Preprocessor -
			- substitution on appearance */
				/* like Java ‘final’ */
int main(void)
{
	float level=1;

	/* if-then-else as in Java */

	if (level <= DANGERLEVEL) /*replaced by 5*/
      		printf("Low on gas!\n");
	else
		printf("Good driver !\n");
}
