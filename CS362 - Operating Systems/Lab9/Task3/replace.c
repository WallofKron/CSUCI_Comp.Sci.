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
	
	printf("REFERENCE STRING:\n{");
    
    for (int i = 0; i < sizeOfRefString; i++){
		
        printf("%d ", referenceString[i]);
	printf("}\n");
    }
    

    
    
	int numOfFaultsLRU = testLRU(numOfFrames, referenceString, sizeOfRefString);
	printf("\nNumber of page faults using LRU: %d\n\n", numOfFaultsLRU);
    
    int numOfFaultsOPT = testOPT(numOfFrames, referenceString, sizeOfRefString);
    printf("\nNumber of page faults using OPT: %d\n\n", numOfFaultsOPT);
    
    int numOfFaultsLFU = testLFU(numOfFrames, referenceString, sizeOfRefString);
    printf("\nNumber of page faults using LFU: %d\n\n", numOfFaultsLFU);
	
	free(referenceString);
}
