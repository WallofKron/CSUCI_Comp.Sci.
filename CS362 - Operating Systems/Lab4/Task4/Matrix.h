/*
 Robert Florence
 Operating Systems
 Prof A.J.
 Lab 4
 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define MAX_SIZE 50

void *matrixThread(void *matrixCell);

void loadMatrices(char *, int ***, int ***, int ***, int *, int *, int *);

void loadMatrix(FILE*, int ***, int, int);

pthread_t **alloc_tids(int, int);

void free_tids(pthread_t **, int);

pthread_t **multiply(int **, int**, int**, int, int, int);

void displayMatrix(int**, int, int);


struct matrixindex {
    int i;
    int j;
    int k;
    int **a;
    int **b;
    int **c;
};
