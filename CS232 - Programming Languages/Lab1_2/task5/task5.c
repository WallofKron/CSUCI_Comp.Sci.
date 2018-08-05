#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[250];
char flag[1]="0";
int length = 0;
int j =0;
int sizearr = 0;
char *arr[];
char *(*ptr)[] = &arr;

int main(void){

    printf("Type some words(0 to finish): \n");
    
    while(strcmp(flag,input) != 0){
        
            scanf("%s",input);
            
        if(strcmp(flag,input) != 0){
            
            length = strlen(input);
            
            arr[j] = (char*)malloc(length+1);
            
            strcpy(arr[j],input);
            
            sizearr++;
            
            j++;
            
        } else {
            printf("Words read: %d\n",sizearr);
            
            for(int i=0; i<sizearr; i++){
                
                printf("%s\n", (*ptr)[i]);
            }
            
            free(*arr);
            
            return 0;
        }
    }
    return 0;
}