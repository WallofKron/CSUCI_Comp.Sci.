/**
 * This implements the LRU page-replacement strategy.
 */
#include "replace.h"

// the page frame list
int *pageTable;
int numOfpages;

// the number of elements in the page list
int nextVictimIndex = 0;

// the last page inserted
int lastReferenced = -1;

// statistics
int numOfFaults = 0;

// this is the sequencxe of pages to serve
int *referenceString;
int refStringLength;

void display(void);
void insert(int);
void updatePageTable(int);
int search(int);

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int n, int *refString, int refStrLen)
{
	numOfpages = n;
	referenceString = refString;
	refStringLength = refStrLen;
	
	pageTable = calloc(numOfpages, sizeof(int));
	
	// we use an impossible page reference of -1 as an initial value
	memset(pageTable, -1, numOfpages * sizeof(int));
	nextVictimIndex = 0;
	
#if DEBUGLEVEL > 2
   printf("      ");
#endif
   
#if DEBUGLEVEL > 0
   display();
#endif
   
	// output a message when inserting a page
	int i;
   for (i = 0; i < refStringLength; i++)
	{
		insert(referenceString[i]);
      
#if DEBUGLEVEL > 2
		//printf("{%3d}", referenceString[i]);
#endif
      
#if DEBUGLEVEL > 0
      display();
#endif
      
	}
   
#if DEBUGLEVEL > 2
   printf("      ");
#endif
   
#if DEBUGLEVEL > 0
   display();
#endif
   
	return numOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insert(int pageNumber)
{
	int searchVal = search(pageNumber);
	
	// if we didn't find it, replace the LRU page
	if (searchVal == -1)
	{
		numOfFaults++;
		pageTable[nextVictimIndex] = pageNumber;
      nextVictimIndex = (nextVictimIndex + 1) % numOfpages;
      
#if DEBUGLEVEL > 2
      printf("*");
#endif
	}
	else
   {
      
#if DEBUGLEVEL > 2
      printf(" ");
#endif
      
      if (pageNumber != lastReferenced)
      {
         /**
          * We only update the page table if the page being
          * referenced was not the last one referenced.
          * If it was the last page referenced, leave the
          * page table as is.
          */
         updatePageTable(searchVal);
         lastReferenced = pageNumber;
      }
   }
}

void updatePageTable(int searchVal)
{
	int mostRecetnlyReferencedPage = pageTable[searchVal];
	
	// if the page to be updated is already the next page to be the victim
	// just increment nextVictimIndex -- jump over the body of the following "if"
	
	// otherwise shift the page references, so the oldest is always the next victim
	// it's like the top of the stack; always pointing to the latest used
	if (mostRecetnlyReferencedPage != pageTable[nextVictimIndex])
	{
		// now shift all elements left making room at the "top of the stack"
      // for the referenced page
      
		int rightIndex = searchVal;
		int leftIndex = (rightIndex == 0) ? numOfpages - 1 : searchVal - 1;
		
		while (rightIndex != nextVictimIndex )
		{
			pageTable[rightIndex] = pageTable[leftIndex];
			rightIndex = leftIndex;
			
			leftIndex = (leftIndex == 0) ? numOfpages - 1 : leftIndex - 1;
		}
		pageTable[rightIndex] = mostRecetnlyReferencedPage;
	}
   
   // at this moment, nextVictimIndex is pointing to the most recenty referenced page
   // the following will make that page the furthest from being a victim (i.e. it will
   // be the top of the stack
	
	nextVictimIndex = (nextVictimIndex + 1) % numOfpages;
}

/**
 * Searches for page pageNumber in the page frame list
 * returns non-negative integer if pageNumber was found
 * returns -1 if pageNumber was not found
 */
int search(int pageNumber)
{
	for (int i = 0; i < numOfpages; i++)
		if (pageNumber == pageTable[i])
			return i;
	return -1;
}

void display(){
    /*
    
	for (int i = 0; i < numOfpages; i++)
   {
#if DEBUGLEVEL > 1
		printf("%s", ((i == nextVictimIndex) ? " ->" : "   "));
#endif
		printf("[%3d]", pageTable[i]);
   }
   printf("\n");
     */
}
