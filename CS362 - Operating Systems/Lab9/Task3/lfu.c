/**
Robert Florence
 Prof AJ/Dolan-Stern
 Lab 9
 Task 3
 */

#include "replace.h"

int *pageTable;     // the page frame list
int numOfpages;

int numFaults = 0;
int starredIndex = -1;

int *referenceString;               // this is the sequence of pages to serve
int refStringLength;

void disply(int);
void insertTo(int, int[], int *refString, int refStrLen);
int lookFor(int);



int testLFU(int n, int *refString, int refStrLen){
    
    numOfpages = n;
    referenceString = refString;
    refStringLength = refStrLen;
    
    pageTable = calloc(numOfpages, sizeof(int));
    
    // we use an impossible page reference of -1 as an initial value
    memset(pageTable, -1, numOfpages * sizeof(int));
    
    
    int freqcounter[refStrLen];             //counter for each individual number that shows up, even if each number in the ref string is a different num from the last, the array will only be as big as refStrLen
    
    
    for (int k = 0; k < refStrLen; k++) {           //init freq counter to 0
        freqcounter[k] = 0;
    }
    
    
    for (int i = 0; i < refStringLength; i++){
        
        insertTo(referenceString[i], freqcounter, refString, refStrLen);
        printf("{%d} - ",referenceString[i]);
        disply(starredIndex);
        starredIndex =-1;
    }
    return numFaults;
}



void insertTo(int pageNumber, int freqcounter[], int *refString, int refStrLen){                    //try to insert a page into the page table
    
    int searchVal = lookFor(pageNumber);
    
    int replacePageIndex = 0;
    
    int lowestNum = 10000;              //arbitrarily large number to find lowest freq.
    
    for (int i = 0; i < numOfpages; i++) {          //for loop to check if theirs an empty spot, and if their is, check to see if value already exists inside page table
        if (pageTable[i] == -1) {
            
            if (searchVal == -1) {
                
                pageTable[i] = pageNumber;
                
                numFaults++;
                
                starredIndex = i;
                
                freqcounter[pageNumber-1]++;        //since this page num was ref, increment it
                return;
            }
        }
    }
    if (searchVal == -1){                   //if num not found in page table, find where to put it into, else skip
        
        for (int y = 0; y < numOfpages; y++) {      //skip through the page table and find the lowest occuring pageNumber
            
            if (freqcounter[(pageTable[y]-1)] < lowestNum) {    //find lowestNum of frequency
                
                lowestNum = freqcounter[(pageTable[y]-1)];
                replacePageIndex = y;
            }
        }
        
        pageTable[replacePageIndex] = pageNumber;
       
        numFaults++;
        
        starredIndex = replacePageIndex;
        
        freqcounter[pageNumber-1]++;

        /*
        printf("\t");
        for (int p = 0; p < refStrLen; p++) {
            printf("%d{%d}  ", p+1, freqcounter[p]);
        }
        printf("\n");
       */
        
    } else {
        freqcounter[pageNumber-1]++;        //if number is in page table, inc freq. because it was referenced
    }
}


int lookFor(int pageNumber){            //search
    
    for (int i = 0; i < numOfpages; i++){
        
        if (pageNumber == pageTable[i]){
            
            return i;
        }
    }
    return -1;
}



void disply(int starredIndex){              //print lines
    
    for (int i = 0; i < numOfpages; i++){
        if (starredIndex == i) {
            
            printf("[*%2d]  ", pageTable[i]);
            
        } else {
            
            printf("[%3d]  ", pageTable[i]);
        }
    }
    printf("\n");
}
