/*
 Robert Florence
 Prof. A.J./Dolan-Stern
 CS 362
 Lab 8
 Task 3
 */
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct invTablePage{                    //each individual Page characteristics
    int pid;            //process id
    int p;                  //page
    unsigned long timestamp;
} invTablePage;


struct Table{                       //table that holds the metadata about Table and
    int frameSize;                      //holds the array of page tables
    int memSize;
    int numPages;         //MUST be an integer
    int d;                  //offset
    struct invTablePage pageTable[10];
};


void initInverted(struct Table *Table, int memSize, int frameSize){

    Table = malloc(sizeof(Table));
    
    if(!Table){
        printf("Malloc Failed - TABLE STRUCT\n");
    }
    
    Table->frameSize = frameSize;
    Table->memSize = memSize;
    Table->d = 0;
    Table->numPages = floor(memSize/frameSize);
    
    
    for (int i = 0; i < Table->numPages; i++){
        
        Table->pageTable[i].p = i;
        Table->pageTable[i].timestamp = 0;
        Table->pageTable[i].pid = 0;
    }
}

void addPage(struct Table *Table, int pid, unsigned long timestamp, int page){
    
    unsigned long tempTS = 9999999999999999999;            //arbitrarily big number to find the lowest Timestamp
    int replslot;                                               //temp var for slot of replacement
    
    if (page == -1) {               //if flag -1, means page to insert into isnt known.
        for (int u = 0; u < Table->numPages; u++){          //search to find open slot
            
            if (Table->pageTable[u].timestamp != 0){
                
                if (Table->pageTable[u].timestamp < tempTS){   //find oldest timestamp
                    tempTS = Table->pageTable[u].timestamp;         //replace if older than current temp T.S.
                    replslot = u;
                }
                
                printf("slot %d taken\n",u);
                
            } else {
                
                printf("slot %d AVAILABLE\n",u);         //if slot available. insert new page
                Table->pageTable[u].pid = pid;
                Table->pageTable[u].timestamp = timestamp;
                printf("Process: %d slotted into page: %d\n", pid, u);
                page = u;
                
                break;
            }
        }
        if (page == -1) {                   //if 'page' never changed, it means that the page table full
            printf("Page at slot %d replaced by PID: %d\n",replslot, pid);
            
            Table->pageTable[replslot].pid = pid;
            Table->pageTable[replslot].timestamp = timestamp;       //replace oldest page with new page
        }
    } else {                        //if page != -1 then, insert spot thats given, test to see if its available
        if (Table->pageTable[page].timestamp == 0) {
            
            printf("slot %d AVAILABLE\n",page);         //if slot available. insert new page
            Table->pageTable[page].pid = pid;
            Table->pageTable[page].timestamp = timestamp;
            printf("Process: %d slotted into page: %d\n", pid, page);
            
        } else {
            
            printf("Page %d already taken!\nReplacing oldest page with newest, instead!\n", page);
            
            for (int h = 0; h < Table->numPages; h++){          //search to find open slot
                
                if (Table->pageTable[h].timestamp != 0){
                    
                    if (Table->pageTable[h].timestamp < tempTS){   //find oldest timestamp
                        tempTS = Table->pageTable[h].timestamp;
                        replslot = h;
                    }
                }
            }
            printf("Page at slot %d replaced by PID: %d\n",replslot, pid);
            
            Table->pageTable[replslot].pid = pid;
            Table->pageTable[replslot].timestamp = timestamp;
        }
    }
}

int translate(struct Table *Table, int pid){

    struct timeval tval;

    int physicalAddress = 0;
    int slotfound = -1;
    
    gettimeofday(&tval,NULL);
    unsigned long curTime = ((1000000 * tval.tv_sec) + tval.tv_usec);

    
    for (int p = 0; p < Table->numPages; p++) {
        if(Table->pageTable[p].pid == pid){
        
            slotfound = p;
        }
    }
    
    if (slotfound == -1){                   //didn't find the PID in page table, add it
        
        addPage(Table, pid, curTime, -1);
    }
    
    for (int p = 0; p < Table->numPages; p++) {         //after add, search PID, calculate and return physical address
        if(Table->pageTable[p].pid == pid){
            
            slotfound = p;
        }
    }
    
    physicalAddress = ((slotfound * Table->frameSize) + Table->d);          // slotfound*framesize  + offset

    
    return physicalAddress;
}

void releaseInverted(struct Table *invTable){

    free(invTable);
    
}
