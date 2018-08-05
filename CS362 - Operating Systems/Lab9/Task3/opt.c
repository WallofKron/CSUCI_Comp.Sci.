/**
 * This implements the OPT page-replacement strategy.
 */

#include "replace.h"

int *pageTable;     // the page frame list
int numOfpages;

int numberOfFaults = 0;

int starIndex = -1;

int *referenceString;               // this is the sequence of pages to serve
int refStringLength;

void dsply(int);
void insertInto(int, int, int *refString, int refStrLen);
int searchFor(int);



int testOPT(int n, int *refString, int refStrLen){
    
    numOfpages = n;
    referenceString = refString;
    refStringLength = refStrLen;
    
    pageTable = calloc(numOfpages, sizeof(int));
    
    // we use an impossible page reference of -1 as an initial value
    memset(pageTable, -1, numOfpages * sizeof(int));
    
    int StringPos = 0;
    
    for (int i = 0; i < refStringLength; i++){
        
        StringPos = i;
        insertInto(referenceString[i], StringPos, refString, refStrLen);
        printf("{%d} - ",referenceString[i]);
        dsply(starIndex);
        starIndex =-1;
    }
    return numberOfFaults;
}



void insertInto(int pageNumber, int StringPos, int *refString, int refStrLen){                    //try to insert a page into the page table

    int searchVal = searchFor(pageNumber);
    
    int distance[numOfpages];
    int replacePageIndex = 0;
    
    for (int i = 0; i < numOfpages; i++) {
        distance[i] = -1;                    //initialize distance array
        }
    
    for (int i = 0; i < numOfpages; i++) {          //for loop to check if theirs an empty spot, and if their is, check to see if value already exists inside page table
        if (pageTable[i] == -1) {
            
            if (searchVal == -1) {
                
            pageTable[i] = pageNumber;
            numberOfFaults++;
                starIndex = i;
            return;
            }
        }
    }
    if (searchVal == -1){                   //if num not found in page table, find where to put it into, else skip
        
        numberOfFaults++;
        for (int j = 0; j < numOfpages; j++) {          //loop through all pages in page table
            
            for (int k = StringPos; k < refStrLen; k++) {         //scan through rest of string finding farthest
                
                if (pageTable[j] == refString[k]) {
                    distance[j] = k - StringPos;
                    break;
                    
                } else {
                    
                    distance[j]++;                  //these aren't the page tables your looking for
                    
                }
            }
        }
        
        int replacingDist = 0;               //init to first page table distance
        
        for (int z = 0; z < numOfpages; z++) {
            
            if (pageTable[z] > replacingDist) {         //if distance value of next page is larger, change to it
                
                replacingDist = pageTable[z];
            }
        }
        
        for (int q = 0; q < numOfpages; q++) {      //find which index to replace
            
            if (distance[q] == replacingDist) {
                
                replacePageIndex = q;          //after finding which page has the largest distance set that index
                break;
            }
        }
        
        if (replacingDist == -1) {
            printf("Replacing first page");
            
        } else {
            
            pageTable[replacePageIndex] = pageNumber;
            starIndex = replacePageIndex;
        }
    }
}


int searchFor(int pageNumber){
    
    for (int i = 0; i < numOfpages; i++){
        
        if (pageNumber == pageTable[i]){
        
            return i;
        }
    }
    return -1;
}



void dsply(int starIndex){
    
    for (int i = 0; i < numOfpages; i++){
        if (starIndex == i) {
            
            printf("[*%2d]  ", pageTable[i]);

        } else {
        
        printf("[%3d]  ", pageTable[i]);
        }
    }
    printf("\n");
}
