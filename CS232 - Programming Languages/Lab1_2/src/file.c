#include <stdio.h>

int main(void) {
	/* file handles */
	FILE *output_file=NULL; 
	
	/* open files for writing*/
	output_file = fopen("cwork.dat", "w");
	if(output_file == NULL)
		return(1);    /* need to do explicit ERROR CHECKING */
	
	/* write some data into the file */
    fprintf(output_file, "Hello there");
	
	/* don’t forget to close file handles */
	fclose(output_file); 
	
    return 0;
}
