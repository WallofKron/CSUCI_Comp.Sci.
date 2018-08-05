#include <stdio.h>
#define DANGERLEVEL 5    /* C Preprocessor -
			- substitution on appearance */
				/* like Java ‘final’ */
int main(void)
{
	float level=1;
    int gaslevel=0;

	/* if-then-else as in Java */
    printf("Gas level?(0 - 10): ");
    scanf("%d", &gaslevel);
    
    if (gaslevel <= DANGERLEVEL){
        
      		printf("Low on gas!\n");
    }else{
        
        printf("Good driver !\n");
}
    
    
    return 0;
}