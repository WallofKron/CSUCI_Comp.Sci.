#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(char *curstrng, char x, char y);

int main(int argc, char *argv[]){
    
    printf("%d \n",argc);
    printf("%s \n",argv[0]);
    printf("%s \n",argv[1]);
    printf("%s \n",argv[2]);
    printf("%s \n",argv[3]);
    printf("%s \n",argv[4]);
    printf("%s \n",argv[5]);
    printf("%s \n",argv[6]);
    
    const int ARRAYSIZE = 100;
    
    char fromchar;
    char tochar;
    
    char inputstring[ARRAYSIZE];
    char outputstring[ARRAYSIZE];
    char tempstrn[ARRAYSIZE];
    
    FILE *inputfile;
    FILE *outputfile;
    
    if(argc > 2){
        
        if(strcmp(argv[1],"-h") == 0){
        
            printf("\n\nCorrect Format/Usage:  sub  fromChar  toChar  srcFile  destFile\n");
        
        } else {
        
            fromchar = *argv[1];
            tochar = *argv[2];
            
            
            if (argc > 3) {
                
                if (strcmp(argv[3],"-f") == 0) {
                    
                    char *filename = argv[4];
                    
                    inputfile = fopen(filename,"r");
                    
                    if (inputfile == NULL){
                    
                        printf("\nFile Doesn't Exist\n");
                        exit(0);
                        
                    } else {
                    
                        fseek(inputfile, 0, SEEK_END);
                        
                        long fsize = ftell(inputfile);
                        
                        fseek(inputfile, 0, SEEK_SET);
                        
                        char bufferstring[fsize + 1];
                        
                        fread(bufferstring, fsize, 1, inputfile);
                        
                        replace(bufferstring,fromchar,tochar);
                        
                        
                        if (strcmp(argv[5],"-o") == 0) {

                            char *outfilename = argv[6];
                            
                            outputfile = fopen(outfilename, "w");
                            
                            fprintf(outputfile,"%s\n",bufferstring);
                            
                            fclose(outputfile);
                            
                        } else {
                        
                        printf("\nOutput: %s\n", bufferstring);
                        
                        }
                        
                    }
                    fclose(inputfile);
                }
                
                if (strcmp(argv[3],"-o") == 0) {
                
                    printf("\nInput: ");
                    scanf("%s",inputstring);
                    
                    replace(inputstring, fromchar, tochar);
                    
                    char *outfilename = argv[4];
                    
                    outputfile = fopen(outfilename, "w");
                    
                    fprintf(outputfile,"%s\n",inputstring);
                    
                    fclose(outputfile);
                
                }
                
            } else {
            
            printf("\nInput: ");
            scanf("%s",inputstring);
            
            strncpy(tempstrn, inputstring, strlen(inputstring));
            
            replace(tempstrn, fromchar, tochar);
            
            strncpy(outputstring, tempstrn, strlen(tempstrn));
            
            printf("Output: %s\n", outputstring);
            
            }
    
        }
    } else {
        
        printf("Please Enter character to change FROM: ");
        scanf(" %c", &fromchar);
        printf("Please Enter character to change TO: ");
        scanf(" %c", &tochar);
        
        printf("\nInput: ");
        scanf("%s",inputstring);
        
        strncpy(tempstrn, inputstring, strlen(inputstring));
        
        replace(tempstrn, fromchar, tochar);
        
        strncpy(outputstring, tempstrn, strlen(tempstrn));
        
        printf("\nOutput: %s\n", outputstring);

        
    } //if no parameters were sent to function call   e.g.  ./sub

    return 0;
}

void replace(char *curstrng, char x, char y) {
    
    int i = 0;

    while(curstrng[i] != '\0'){
        
        if(curstrng[i] == x){
            curstrng[i] = y;
        }
        
        i++;
    }// end while loop
}