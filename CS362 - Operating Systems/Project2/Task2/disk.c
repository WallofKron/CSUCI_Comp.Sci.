#include "disk.h"

void start_timer(void)
{
    struct itimerspec value;

    value.it_value.tv_sec = 1;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 1;
    value.it_interval.tv_nsec = 0;

    timer_create (CLOCK_REALTIME, NULL, &gTimerid);

    timer_settime (gTimerid, 0, &value, NULL);

}

void stop_timer(void)
{
    struct itimerspec value;

    value.it_value.tv_sec = 0;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_settime (gTimerid, 0, &value, NULL);
}

void timer_callback(int sig){
	
    printf("\n\n\nCaught timer signal: %d !!\n", sig);
    
    srand(time(NULL));
    int rorw = rand() % 2;		//roll for read or write.	-----   1- write   0-read
	int randlog = rand() % 30;		//roll for logic address. restricting to PHYS ADDRESS: head 0 cyl 0 sect 0-30 for sake of our project
	int randnumblock = (rand() % 5) + 1;		//roll for num blocks. restricting to 1 - 5 for sake of project simplicity. could be expanded to entire disk space.
	
	int randstringlength = rand() % 40;			//roll for randomly generated string length. up to 40 chars.
	
	char *newstring = randstring(randstringlength);
	
	//printf("rorw - %d\nrandlog - %d\nnumblock - %d\nstrnlen - %d\nnewstrn - %s\n", rorw, randlog, randnumblock, randstringlength, newstring);
		//print statement is testing the values of randomly generated content
	
	time_t rawtime;
	struct tm * actualtime;
	
	time(&rawtime);
    actualtime = localtime(&rawtime);
      int hour = actualtime->tm_hour;
      int minute = actualtime->tm_min;
      int second = actualtime->tm_sec;
	
	physaddr_t *localphaddr = malloc(sizeof(physaddr_t));
    log_to_phys(randlog, localphaddr);
	
		
		if(rorw == 1){
			
			if(writeBlock(randlog, randnumblock, newstring) == 1){
			  printf("Write Success\n");
			  printf("Random LOGIC Address - %d\nCORRESPONDING PHYSICAL ADDRESS - HEAD: %d      CYL: %d      SECT: %d\nnumber of blocks written - %d\nstrnlen - %d\nString Written - %s\nTime Performed - %d:%d:%d\n", randlog, localphaddr->head, localphaddr->cyl, localphaddr->sect, randnumblock, randstringlength, newstring, hour, minute, second);
	
                    } else {
                    
                        printf("Write FAIL\n");
                    }
			
		} else {
			
			if(readBlock(randlog, randnumblock, (void**)newstring) == 1){
				  printf("\nRead Success\n");
				  printf("Random LOGIC Address - %d\nCORRESPONDING PHYSICAL ADDRESS - HEAD: %d      CYL: %d      SECT: %d\nnumber of blocks Read - %d\nstrnlen - %d\nTime Performed - %d:%d:%d\n", randlog, localphaddr->head, localphaddr->cyl, localphaddr->sect, randnumblock, randstringlength, hour, minute, second);

                    } else {
                    
                        printf("\nRead FAIL\n");
                    }
				
				}
    count--;
	free(localphaddr);
}

char *randstring(size_t length){

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
            randomString[length] = '\0';
        }
    }
    return randomString;
}
/*int main(int ac, char **av)
{
    (void) signal(SIGALRM, timer_callback);
    start_timer();
    while(count >= 0);
}*/




int log_to_phys(int logaddr, physaddr_t *phaddr){

    if(logaddr >= 0 && logaddr < MAX_LOGICAL_SECTOR){
    
    phaddr->cyl = (logaddr / (NUM_OF_HEADS * NUM_OF_SECTS));
    phaddr->head = ((logaddr / NUM_OF_SECTS) % NUM_OF_HEADS);
    phaddr->sect = ((logaddr % NUM_OF_SECTS) + 1);
    
        return 1;               //successful conversion
        
    } else {
    
        return -1;               //failed conversion
    }
}




int phys_to_log(physaddr_t *phaddr){
    
    if(phaddr != NULL){
        
return ((phaddr->cyl * NUM_OF_HEADS + phaddr->head) * NUM_OF_SECTS) + (phaddr->sect - 1);
  
    } else {
        
        return -1;           //if phaddr is null return failed call, else return logaddr
        
    }
}



int readBlock(int logical_block_num, int num_of_sectors, void **buffer){

    physaddr_t *localphaddr = malloc(sizeof(physaddr_t));
    char tempbuff[(num_of_sectors * (SECT_SIZE-1))];        //used to read data from disk
        
        
    if(log_to_phys(logical_block_num, localphaddr) == 1){        //set up physical address
    
        for (int j = 0; j < num_of_sectors; j++) {
    
            for (int i = 0; i < (SECT_SIZE-1); i++) {
        
                tempbuff[(j*(SECT_SIZE-1)) + i] = disk[localphaddr->head][localphaddr->cyl][localphaddr->sect + j][i];
            }
        }
    
        printf("From LogAddress: %d, we read: ", logical_block_num);        //print buffer
        
        for (int z = 0; z < strlen(tempbuff); z++) {
            printf("%c", tempbuff[z]);
        }
        
        buff = tempbuff;
        
        free(localphaddr);              //release malloc'd space
        return 1;

    } else {
    
        printf("\nLogical Address is not readable");

        free(localphaddr);              //release malloc'd space
        return 0;
    }
}




int writeBlock(int logical_block_num, int num_of_sectors, void *buffer){

    physaddr_t *localphaddr = malloc(sizeof(physaddr_t));
    log_to_phys(logical_block_num, localphaddr);
    
    int bufflen = strlen((char*)buffer);
    int position = 0;
    
    if(log_to_phys(logical_block_num, localphaddr) == 1){
        
        for (int i = 0; i < num_of_sectors; i++) {
    
            for (int j = 0; j < (SECT_SIZE-1); j++) {
                if (position < bufflen){
            
               disk[localphaddr->head][localphaddr->cyl][localphaddr->sect + i][j] =  *((char*)buffer + position);                          //writing contents of void pointer to disk space
                }
                position++;
                disk[localphaddr->head][localphaddr->cyl][localphaddr->sect + j][SECT_SIZE-1] = '\0';
        }
    }
        free(localphaddr);              //release malloc'd space
        return 1;
        
    } else {
    
        
        
    
        free(localphaddr);              //release malloc'd space
        return 0;
    }
    return -1;
}



int main(int argc, char *argv[]){
    
    physaddr = calloc(1, sizeof(physaddr_t));       //initiate physaddr struct to use with case 1 and 2
    
    
    while(choice != -1){
        
        printf("\n\nMENU:\n1). Log->Phys\n2). Phys->Log\n3). Read\n4). Write\n5). Random Disk Events\n6). EXIT\n");
        printf("\nEnter a Menu Choice: ");
        
        scanf("%d", &choice);
        
            switch (choice) {
                case 1:
                    printf("\nEnter Logical Address: ");
                    scanf("%d", &logicalAddress);
                    
                    int result = log_to_phys(logicalAddress, physaddr);
                    
                    if (result != -1) {
                    
                    printf("\nCORRESPONDING PHYSICAL ADDRESS\nHEAD: %d\nCYL: %d\nSECT: %d\n", physaddr->head, physaddr->cyl, physaddr->sect);
                    } else {
                    
                        printf("Failed to translate LOG -> PHYS");
                    }
                    
                    break;
                
                case 2:

                    printf("\nEnter Head: ");
                    scanf("%d", &physaddr->head);

                    printf("\nEnter Cyl: ");
                    scanf("%d", &physaddr->cyl);
                    
                    printf("\nEnter Sect: ");
                    scanf("%d", &physaddr->sect);
                    
                    printf("\nPHYSICAL ADDRESS - Translating\nCYL: %d\nHEAD: %d\nSECT: %d\n", physaddr->cyl, physaddr->head, physaddr->sect);

                    logicalAddress = phys_to_log(physaddr);

                    printf("\nCorresponding Logical Address: %d\n", logicalAddress);

                    

                    break;
                
                case 3:
                    
                    printf("Enter Logical address to READ from: ");
                    scanf("%d", &logicBlockNum);
                    
                    printf("Enter Number of sectors to read: ");
                    scanf("%d", &NumSectors);
                    
                    if(readBlock(logicBlockNum, NumSectors, buff) == 1){
                        
                        /*for (int j = 0; j < strlen((char*)buff); j++) {
                        
                        printf("\n%c", *((char*)buff + j));
                        }*/                         //we can also access the data from Main
                        
                        printf("\n Read Success");
                    } else {
                    
                        printf("\n Read FAIL");
                    }

                    break;
                
                case 4:
                    
                    printf("Enter Logical address to WRITE to: ");
                    scanf("%d", &logicBlockNum);
                    
                    printf("Enter message to WRITE: ");
                    
                    scanf("\n%[^\n]", writeStrng);
                    
                    
                    NumSectors = ((strlen(writeStrng) / (SECT_SIZE - 1)) + 1);
                    
                    buff = writeStrng;                  //buff's address points to writeString
                    
                    if(writeBlock(logicBlockNum, NumSectors, buff) == 1){
                    
                        printf("\n Write Success");

                    } else {
                    
                        printf("\n Write FAIL");
                    }
                    
                    break;
                
                
                    
                    
                case 5:
                
                (void) signal(SIGALRM, timer_callback);
				start_timer();
				while(count >= 0);
				stop_timer();	
                
                
                break;
                
                
                
                 case 6:
                choice = -1;
                    break;
                
                default:
                    printf("\n\nNot a valid Menu Option\n");
                    break;
        }
    }
    free(physaddr);
    return 0;
}
