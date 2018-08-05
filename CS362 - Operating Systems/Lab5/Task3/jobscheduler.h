/*
 Robert Florence
 Prof. A.J/Dolan-Stern
 CS362
 Lab 5
 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 5     //max size of mode is 4 + 1 for null term char.
#define ProcessMax 50    //for testing/creating arrays
#define True 1

char jobMode[MAX_SIZE];

int processcounter = 0;
int numinqueue = 0;
int quanta = 0;
int timeclock = 0;
int quantacount = 0;
int arrivedprocesses = 0;


char ch;

int CPUcur[3];

int processqueue[(ProcessMax * 3)];

int processes[(ProcessMax * 3)]; //each process gets three slots of array. For; number, arrival, and burst time.
int WaitTime[ProcessMax];

void readprocesses();

void displayProcessQueue();

void shiftProcessQueue();

void quantaswap();

void processtermination();

void updatewaittime();

void searchandprocess();
