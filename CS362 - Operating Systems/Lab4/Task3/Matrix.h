#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define MAX_SIZE 50

int **a, **b, **c;
int m, k, n;

void *matrixThread(void *cellIndex);

void loadMatrices(char *fileName);

void allocateMatrix(int ** build, int m, int n);

void loadMatrix(FILE*, int ***, int, int);

void multiply(int **, int **, int **, int, int, int);

void displayMatrix(int **, int, int, char*);

struct matrixindex {
	int row;
	int column;
    int middle;
};
