/*
 Robert Florence
 Prof. A.J/Dolan-Stern
 CS362
 Lab 5
 
 */

#include "jobscheduler.h"

int main(int argc, char *argv[]){
    
    scanf("%s",jobMode);        //get which job mode this is
    
    if (strncmp(jobMode,"FCFS",strlen(jobMode))==0) {                       //FCFS
        readprocesses();

        CPUcur[0] = processes[0];
        CPUcur[1] = processes[1];
        CPUcur[2] = processes[2];
        // place the first process in the CPU, because its the only process. INIT.
        
        arrivedprocesses++;
        
        printf("T0: Process %d Arrived!\n", processes[0]);
        printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
        displayProcessQueue();

        for(timeclock = 0; True; timeclock++){
            
            if (CPUcur[2] == 0) {               // process finished
                
                printf("T%d: Process %d Finished!\n", timeclock, CPUcur[0]);
                
                processtermination();
                numinqueue--;
                
                printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                displayProcessQueue();
            }
            if (timeclock != 0) {
                
                if (processes[(arrivedprocesses * 3) + 1] == timeclock){        //process arrival
                    
                    processqueue[((numinqueue) * 3)] = processes[(arrivedprocesses * 3)];
                    processqueue[((numinqueue) * 3) + 1] = processes[(arrivedprocesses * 3) + 1];
                    processqueue[((numinqueue) * 3) + 2] = processes[(arrivedprocesses * 3) + 2];
                    
                    numinqueue++;               //add process into queue
                    
                    arrivedprocesses++;         //increment number of processes arrived
                    
                    printf("T%d: Process %d Arrived!\n", timeclock, processqueue[((numinqueue - 1) * 3)]);
                    printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                    displayProcessQueue();
                }
            }
            CPUcur[2]--;
            updatewaittime();
            
            if (numinqueue == 0 && arrivedprocesses == processcounter && CPUcur[2] == 0) {
                int totalwaittime = 0;
                
                for (int g = 0; g < processcounter; g++) {
                    
                    totalwaittime += WaitTime[g];
                }
                
                double average = (totalwaittime/processcounter);
                printf("Average Waiting Time: %f\n",average);
                
                exit(0);
            }
        }
        
    } else if (strncmp(jobMode,"SJF",strlen(jobMode))==0) {                         //SJF
       
        readprocesses();
        
        CPUcur[0] = processes[0];
        CPUcur[1] = processes[1];
        CPUcur[2] = processes[2];
        // place the first process in the CPU, because its the only process. INIT.
        
        arrivedprocesses++;
        
        printf("T0: Process %d Arrived!\n", processes[0]);
        printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
        displayProcessQueue();
        
        for(timeclock = 0; True; timeclock++){
            
            if (CPUcur[2] == 0) {               // process finished
                printf("T%d: Process %d Finished!\n", timeclock, CPUcur[0]);
                
                searchandprocess();
                numinqueue--;
                
                printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                displayProcessQueue();
                
            }
            
            if (timeclock != 0) {
                
                if (processes[(arrivedprocesses * 3) + 1] == timeclock){        //process arrival
                    
                    processqueue[((numinqueue) * 3)] = processes[(arrivedprocesses * 3)];
                    processqueue[((numinqueue) * 3) + 1] = processes[(arrivedprocesses * 3) + 1];
                    processqueue[((numinqueue) * 3) + 2] = processes[(arrivedprocesses * 3) + 2];
                    
                    numinqueue++;               //add process into queue
                    
                    arrivedprocesses++;         //increment number of processes arrived
                    
                    printf("T%d: Process %d Arrived!\n", timeclock, processqueue[((numinqueue - 1) * 3)]);
                    printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                    displayProcessQueue();
                    
                }
            }
            
            quantacount++;
            CPUcur[2]--;
            
            updatewaittime();
            
            if (numinqueue == 0 && arrivedprocesses == processcounter && CPUcur[2] == 0) {
                
                int totalwaittime = 0;
                
                for (int g = 0; g < processcounter; g++) {
                    
                    totalwaittime += WaitTime[g];
                }
                
                double average = (totalwaittime/processcounter);
                printf("Average Waiting Time: %f\n",average);
                
                exit(0);
            }
        }
        
        
    } else if (strncmp(jobMode,"RR",strlen(jobMode))==0) {                      // Round Robin
        
        scanf("%d",&quanta);
        
        readprocesses();
        
        CPUcur[0] = processes[0];
        CPUcur[1] = processes[1];
        CPUcur[2] = processes[2];
        // place the first process in the CPU, because its the only process. INIT.
        
        arrivedprocesses++;
        
        printf("T0: Process %d Arrived!\n", processes[0]);
        printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
        displayProcessQueue();
        
        for(timeclock = 0; True; timeclock++){
        
            if (CPUcur[2] == 0) {               // process finished
                printf("T%d: Process %d Finished!\n", timeclock, CPUcur[0]);

                processtermination();
                numinqueue--;
                
                printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                displayProcessQueue();
            
                }
            
            if (timeclock != 0) {
                
                if (quantacount == quanta) {        //quanta swap
             
                    quantacount = 0;
                    
                    quantaswap();
                
                    printf("T%d: Quanta expired!\n", timeclock);
                    printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                    displayProcessQueue();
                }
            
                if (processes[(arrivedprocesses * 3) + 1] == timeclock){        //process arrival
                
                    processqueue[((numinqueue) * 3)] = processes[(arrivedprocesses * 3)];
                    processqueue[((numinqueue) * 3) + 1] = processes[(arrivedprocesses * 3) + 1];
                    processqueue[((numinqueue) * 3) + 2] = processes[(arrivedprocesses * 3) + 2];
                
                    numinqueue++;               //add process into queue

                    arrivedprocesses++;         //increment number of processes arrived
                    
                    printf("T%d: Process %d Arrived!\n", timeclock, processqueue[((numinqueue - 1) * 3)]);
                    printf("CPU: P%d(%d)\n",CPUcur[0],CPUcur[2]);
                    displayProcessQueue();
                
                }
            }
            
            quantacount++;
            CPUcur[2]--;
            
            updatewaittime();
                
            if (numinqueue == 0 && arrivedprocesses == processcounter && CPUcur[2] == 0) {
                
                int totalwaittime = 0;
                
                for (int g = 0; g < processcounter; g++) {
                    
                    totalwaittime += WaitTime[g];
                }
                
                double average = (totalwaittime/processcounter);
                printf("Average Waiting Time: %f\n",average);
                
                exit(0);
            }
        }
        
    } else {
        printf("\n\nWrong File Mode! Exiting!\n\n");
        exit(0);
    }                       //no correct file mode passed as input.
    
    
}

void readprocesses(){

    while ((ch = fgetc(stdin)) != EOF) {
    
            scanf("%d",&processes[((processcounter-1) * 3)]);
            
            scanf("%d",&processes[((processcounter-1) * 3) + 1]);
        
            scanf("%d\n",&processes[((processcounter-1) * 3) + 2]);
            
            processcounter++;      //count how many lines
    }
        processcounter--;
}

void shiftProcessQueue(){

    int length = 0;
    
    length = (sizeof(processqueue) / sizeof(int));
    
    for (int j = 0; j < length; j++){
        processqueue[j] = processqueue[j+3];
    }


}

void updatewaittime(){

    for (int l = 0; l < numinqueue; l++) {
        WaitTime[processqueue[(l*3)]]++;
    }

}

void quantaswap(){

    int temp[3];    // to store the current process from the CPU
    
    temp[0] = CPUcur[0];
    temp[1] = CPUcur[1];
    temp[2] = CPUcur[2];
    
    CPUcur[0] = processqueue[0];        // transfer first process on queue to CPU
    CPUcur[1] = processqueue[1];
    CPUcur[2] = processqueue[2];
    
    shiftProcessQueue();            //shift everything down 3
    
    processqueue[((numinqueue -1) * 3)] = temp[0];   // put old CPU process at end of queue
    processqueue[((numinqueue - 1) * 3) + 1] = temp[1];
    processqueue[((numinqueue - 1) * 3) + 2] = temp[2];

    quantacount = 0;
}

void searchandprocess(){
    int templow = 200;                      //the cpu bursts less than 200 will be used
    int nextProcess = 0;
    
    for (int y = 0; y < numinqueue; y++) {
        
        if (processqueue[(y * 3) + 2] < templow){
        
            templow = processqueue[(y * 3) + 2];
            nextProcess = (y * 3);
        }
    }
    
    CPUcur[0] = processqueue[nextProcess];        // transfer lowest CPU burst process from queue to CPU
    CPUcur[1] = processqueue[nextProcess + 1];
    CPUcur[2] = processqueue[nextProcess + 2];
    
    int remainingprocesses = (numinqueue - (nextProcess/3));
    
    for (int p = 0; p < (remainingprocesses * 3); p++) {
    
        processqueue[p+nextProcess] = processqueue[p+nextProcess+3];
    }                                                //remove process from queue

    processqueue[((numinqueue) * 3)] = 0;           // put zeros at end of queue, shifted others down
    processqueue[((numinqueue) * 3) + 1] = 0;
    processqueue[((numinqueue) * 3) + 2] = 0;
}


void processtermination(){

    CPUcur[0] = processqueue[0];        // transfer first process on queue to CPU
    CPUcur[1] = processqueue[1];
    CPUcur[2] = processqueue[2];
    
    shiftProcessQueue();            //shift everything down three
    
    processqueue[((numinqueue) * 3)] = 0;   // put old CPU process at end of queue
    processqueue[((numinqueue) * 3) + 1] = 0;
    processqueue[((numinqueue) * 3) + 2] = 0;

    quantacount = 0;
}

void displayProcessQueue(){

    printf("<Queue>: ");

    for (int i = 0; i < numinqueue; i++) {
        
        printf("P%d",processqueue[(i*3)]);
        
        printf("(%d), ",processqueue[(i*3) + 2]);
    }
    printf("\n\n");

}
