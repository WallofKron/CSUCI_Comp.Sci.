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

#define PIDrange 100              //for generating random PID
#define OFFrange 50             //for generating random offset location

#define Fsize 10
#define Msize 100  //for testing purposes

extern void releaseInverted(struct Table *invTable);
extern void initInverted(struct Table *Table, int memSize, int frameSize);
extern int translate(struct Table *Table, int pid);
extern void addPage(struct Table *node, int pid, unsigned long timestamp, int page);

int tempPid;
int tempOffset;
int userPID = 0;
int userPage = -1;

char response;

unsigned long startTime;
unsigned long curTime;

int main(int argc, char* argv[]){

    struct timeval tval;
    gettimeofday(&tval,NULL);
    startTime = ((1000000 * tval.tv_sec) + tval.tv_usec);
    
    //printf("%d\n %d\n  %d\n",Fsize,Msize);
    tempOffset = (rand() % OFFrange);
    
    struct Table CPU;
    
    initInverted(CPU, Msize, Fsize);
    
    CPU->d = tempOffset;
    
    for (int j = 0; j < CPU->numPages; j++){         //generate initial pages. Test
        
        tempPid = (rand() % PIDrange);              //using random PID's
        gettimeofday(&tval,NULL);
        curTime = ((1000000 * tval.tv_sec) + tval.tv_usec);
        addPage(CPU, tempPid, curTime, j);              //new page goes in page j.
        
    }
    
    while(1){                                   //Display page table and Menu
        
        printf("PAGE TABLE:\n");

        for (int k = 0; k < CPU->numPages; k++){
            printf("PID: %d\tPage: %d\tTimestamp: %ld", CPU.pageTable[k]->pid, CPU.pageTable[k]->p, CPU.pageTable[k]->timestamp);
        }
        
        printf("Menu:\n\ta - add new page\n\tp - Physical Address\n\tq/e - quit/exit\n\nPAGE TABLE: \n");
        
        printf("Input Option: ");                   //get input for menu

        response = getchar();
        int PIDtemp = 0;
        
        switch (response) {
            case 'a':                                 //add input option

                gettimeofday(&tval,NULL);
                curTime = ((1000000 * tval.tv_sec) + tval.tv_usec);

                while (userPID <= 0) {
                    printf("\nInput PID of new Page to add: ");
                    scanf("%d", &userPID);
                    printf("\n");

                    printf("\nInput Page #: ");
                    scanf("%d", &userPage);
                    printf("\n");

                    if (!(userPage >= 0 && userPage <= CPU->numPages)){
                        userPage = -1;
                    }
                    
                    if (userPID > 0){

                        addPage(CPU, userPID, curTime, userPage);           //-1 = flag if not know where to input new page/invalid page
                        break;
                        
                    } else {
                        printf("\nIncorrect PID input!\n");
                    }
                }
                break;
            case 'p':
                printf("Physical Address Translation-\nInput PID: ");
                scanf("%d", &PIDtemp);
                translate(CPU, PIDtemp);
                break;
                
            case 'e':
                printf("\nProgram EXIT!\n\n");
                exit(0);
                break;
                
            case 'q':
                printf("\nProgram QUITTING!\n\n");
                exit(0);
                break;
                
            default:
                printf("\nINVALID MENU OPTION!\n\n");
                break;
        }
    }
    
    
    releaseInverted(&CPU);
    
    
    return 0;
}

