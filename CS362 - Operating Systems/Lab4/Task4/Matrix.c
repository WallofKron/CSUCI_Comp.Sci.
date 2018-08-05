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
    
    printf("%s",filename);
    
    loadMatrices(filename);     //allocate space, initialize the 3 matrices, then load the first 2 matrices from the file
    
    
    multiply(a, b, c, m, k, n);
    
    //multiply a * b to get c

    displayMatrix(a, m, k, "A");

    displayMatrix(b, k, n, "B");

    displayMatrix(c, m, n, "C");
    
    free(a);
    free(b);
    free(c);
    
    //release/free allocated memory. Undo Malloc
    
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

    scanf("%d %d %d", &m, &k, &n);  //first three ints are size specifications

    allocateMatrix(a,m,k);
    
    allocateMatrix(b,k,n);
    
    allocateMatrix(c,m,n);
    
    //allocating space for Rows * size of integer pointer array
    //then allocating space for each column int pointer array within the row integer pointer array
    
    loadMatrix(fp, &a, m, k);
    
    loadMatrix(fp, &b, k, n);

    //once the values are loaded from the file close the file
    
    fclose(fp);
}

void allocateMatrix(int ** build, int rows, int columns){

    build = (int **)malloc(sizeof(int *) * rows);
    
    for(int counter = 0; counter < rows; counter++){
        
        build[counter] = (int *)malloc(sizeof(int) * columns);
    }
    
    for(int i=0; i < m; i++) {
        
        for(int j=0; j < n; j++) {
            
            build[i][j] = 0;
        }
    }
    
    //allocate space for target 2-d array and initialize all values
    
}


void loadMatrix(FILE* fp, int ***tempload, int m, int k){

    for(int i = 0; i < m; i++){
        
        for(int j = 0; j < k; j++){
            
            scanf("%d ",tempload[i][j]);
        }
    }
    
}

void free_tids(pthread_t **, int){




}


pthread_t **alloc_tids(int, int){




}



pthread_t **multiply(int **, int**, int**, int, int, int){

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
        
        
        if (err != 0){          //czech to see if thread is successfully created
            
            printf("Can't Create Thread :[%s]", strerror(err));
        
        }else{
            
            printf("Thread created successfully\n");
        }
    }

}

void displayMatrix(int **temp, int m, int k, char* name){

	printf("\nMatrix %s\n--------\n",name);

for(int i=0; i<m; i++){
	
	printf("| ");
		
	for(int j = 0; j<k; j++){

	printf("%d ",temp[i][j]);

	}
	printf("|\n");
    }
	printf("\n");
}

