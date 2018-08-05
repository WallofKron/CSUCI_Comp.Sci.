#include <stdio.h>

int main(void)
{
	int nstudents = 0; /* Initialization, required */
    int nfaculty = 0;
	
	printf("How many students does CSUCI have ?:");
 	scanf ("%d", &nstudents);  /* Read input */
	printf("CSUCI has %d students.\n", nstudents);
    
    
    printf("How many faculty does CSUCI have ?:");
    scanf ("%d", &nfaculty);  /* Read input */
    printf("CSUCI has %d faculty.\n", nfaculty);
    
    double ratio = (nstudents/nfaculty);
    printf("CSUCI's student to faculty ratio is %.1f.\n", ratio);
    
    
	return 0;
}


