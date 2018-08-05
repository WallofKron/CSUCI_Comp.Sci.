#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[255];
    char newname[200];
    char newstr[204];
    
    FILE *output_file = NULL;
    FILE *inputfile = NULL;
    
    inputfile = fopen("data.txt","r");
    
    if(inputfile == NULL){
        
        return(1);    /* need to do explicit ERROR CHECKING */
    }
    
    fgets(buffer, sizeof(buffer), inputfile);
    printf("content of file: %s\n", buffer);
    
    printf("new file name: ");
    scanf("%s", &newname);
    
    strcat(newstr,newname);
    strcat(newstr,".txt");
    
    output_file = fopen(newstr, "w");
    
    if(output_file == NULL){
    
        return(1);    /* need to do explicit ERROR CHECKING */
    }
    
    fprintf(output_file, buffer);
    
    fclose(output_file);
    fclose(inputfile);
    
    return 0;
}