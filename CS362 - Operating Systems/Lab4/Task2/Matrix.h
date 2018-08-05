#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


#define MAX_SIZE 50

int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], c[MAX_SIZE][MAX_SIZE];
int m, k, n;

void *matrixThread(void *cellIndex);

void loadMatrices(char *fileName);

//void loadMatrix(FILE*, int [][MAX_SIZE], int, int);

void multiply(int[][MAX_SIZE], int[][MAX_SIZE], int[][MAX_SIZE], int, int, int);

void displayMatrix(int [][MAX_SIZE], int, int, char*);

struct matrixindex {
	int row;
	int column;
    int middle;
};
