/*
 *  replace.c
 *  Created by AJ Bieszczad on 4/9/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 */

#include "replace.h"
#include <time.h>

int main(int argc, char *argv[])
{
	int sizeOfRefString;
    long double RunningLRU = 0;
    int numOfFaultsLRU = 0;
    long double RunningLFU = 0;
    int numOfFaultsLFU = 0;
    long double RunningOPT = 0;
    int numOfFaultsOPT = 0;
    
    if (argc < 4){
		oops("Usage:\n   replace <num of frames> <ref string length> <value range>\n   replace <number of frames> -s <reference string> \n", 1);
        exit(1);
    }
    
	int numOfFrames = atoi(argv[1]);
	
    if (argv[2][0] == '-'){
	
        sizeOfRefString = argc - 3; // prog name + num of frames + '-s'
    
    }else{
		
        sizeOfRefString = atoi(argv[2]);
    }
    
	int *referenceString = calloc(sizeOfRefString, sizeof(int));
	
    if (argv[2][0] == '-'){
		for (int i = 3; i < argc; i++) {
			referenceString[i - 3] = atoi(argv[i]);
		}
    } else {
		int range = atoi(argv[3]);
		
		// create a random page reference sequence from [0, range-1]
		srand((unsigned int)time(NULL));
		for (int i = 0; i < sizeOfRefString; i++)
			referenceString[i] = rand() % range;
	}
	
	printf("FIRST REFERENCE STRING:\n{");
    
    for (int i = 0; i < sizeOfRefString; i++){
		
        printf("%d ", referenceString[i]);
	printf("}\n");
    }
    
    
    
    
    int counter = 0;
    int r = ((rand() % 5) + 1);
    
    
    while(counter <= 0 || counter > 10000) {
        
        printf("How Many times do you want to test random strings(1-5): ");
        scanf("%d", &counter);
    }
    
    for(int q = 0; q < counter; q++){
    
        for (int t = 0; t < sizeOfRefString; t++) {
            
            int r = ((rand() % 5) + 1);
            referenceString[t] = r;
        }
        
        numOfFaultsLRU = testLRU(numOfFrames, referenceString, sizeOfRefString);
        RunningLRU = numOfFaultsLRU + RunningLRU;
        numOfFaultsLRU = 0;
        
        numOfFaultsOPT = testOPT(numOfFrames, referenceString, sizeOfRefString);
        RunningOPT = numOfFaultsOPT + RunningOPT;
        numOfFaultsOPT = 0;
        
        numOfFaultsLFU = testLFU(numOfFrames, referenceString, sizeOfRefString);
        RunningLFU = numOfFaultsLFU + RunningLFU;
        numOfFaultsLFU = 0;
    
        printf("\n%d). LRU: %Lf\t OPT: %Lf\t LFU: %Lf\n ", q+1, RunningLRU, RunningOPT, RunningLFU);
    }
    printf("\n------ LRUavg: %Lf\t OPTavg: %Lf\t LFUavg: %Lf ------\n ", (RunningLRU/counter), (RunningOPT/counter), (RunningLFU/counter));
	
	free(referenceString);
}
