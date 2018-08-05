/*
 Robert Florence
 Operating Systems
 Prof A.J.
 Lab 4
 
 
 */
#include "Matrix.h"

int main(int argc, char *argv[]){

    printf("\nMATRIX MULTIPLICATION!\n\n");
    
    char filename[MAX_SIZE];

    if (argc >= 2){
        
        strcpy(filename,argv[1]);
        
    } else {
    
        printf("Please Input File Name:  ");
        scanf("%s",filename);
        
    }
    
    loadMatrices(filename);
    
    multiply(a, b, c, m, k, n);

    displayMatrix(a, m, k, "A");

    displayMatrix(b, k, n, "B");

    displayMatrix(c, m, n, "C");
    
    
return 0;
}

void *matrixThread(void *cellIndex){
    
    struct matrixindex* newstruct = (struct matrixindex*)cellIndex;
    
    //casting the void pointer cellIndex to be a new matrixindex struct
    
    c[newstruct->row][newstruct->column] = 0;
    
    for(int counter = 0; counter < newstruct->middle; counter++){
    
    c[newstruct->row][newstruct->column] += (a[newstruct->row][counter] * b[counter][newstruct->column]);
    
    }
    return NULL;
}

void loadMatrices(char *fileName){

FILE* fp;
    
fp = freopen(fileName, "r", stdin);
    
    if (fp == NULL) {
        
        printf("\nFile Open Failed\n");
        
        exit(0);
    }

scanf("%d %d %d", &m, &k, &n);

for(int i = 0; i < m; i++){
    
	for(int j = 0; j < k; j++){

	scanf("%d",&a[i][j]);
	}
}

for(int p=0; p<k; p++){
    
	for(int l = 0; l<n; l++){

	scanf("%d",&b[p][l]);
	}
}

fclose(fp);
}

/*void loadMatrix(FILE* fp, int temp[][MAX_SIZE], int m, int k){

}*/

void multiply(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int m, int k, int n){

    int numthreads = (m * n);
    
    pthread_t tid[(numthreads)];
    
    struct matrixindex strcttothrd[numthreads];
    
    int err;
    
    for(int f = 0; f < numthreads; f++){        // f is our counter for the loop
        
        strcttothrd[f].row = floor((f / m));
        strcttothrd[f].column = floor((f % n));
        strcttothrd[f].middle = k;
        
        //creating the struct values for each threads struct
        
        
        err = pthread_create(&(tid[f]), NULL, &matrixThread, &strcttothrd[f]);
        
        //passing the struct to thread as the 4th argument
        //passes the function matrixthread to new thread
        
        
        if (err != 0){               //czech to see if thread is successfully created
            printf("Can't Create Thread :[%s]", strerror(err));
        
        }else{
            printf("Thread created successfully\n");
        }
    }



}

void displayMatrix(int a[][MAX_SIZE], int m, int k, char* name){

	printf("\nMatrix %s\n--------\n",name);

for(int i=0; i<m; i++){
	
	printf("| ");
		
	for(int j = 0; j<k; j++){

	printf("%d ",a[i][j]);

	}
	printf("|\n");
    }
	printf("\n");
}

