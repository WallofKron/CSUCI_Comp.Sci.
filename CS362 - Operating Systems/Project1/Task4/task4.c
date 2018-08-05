/*
 Robert Florence
 Prof. A.J/Dolan-Stern
 CS362
 Project 1 Task4
 */

#include "task4.h"


void createFS(){

    memory = calloc(NUM_BLOCKS, sizeof(struct node));    //malloc space for 16 blocks not 2^16
    bitvector = calloc(NUM_BLOCKS, sizeof(char));     //malloc space of bit vector - num blocks
}





void createFile(char NAME[MAX_NAME_LENGTH], unsigned short owner, data_t inputData[DATA_SIZE]){

    int NewIndex = emptyIndexSearch();                  //find open block in memory
    
    if (NewIndex == 0){
        printf("\nNo empty spot in memory to create new File!\n");
        //exit(0);
        
    } else {
        
        
        //CREATING FILE NODE AND SETTING VAR'S
        unsigned long curTime = time(NULL);             // getting the epoch time in ms, which can be easily converted to Human time/date
        
        memory[NewIndex].type = File;             //setting type to FILE
        
        strncpy(memory[NewIndex].content.fd.name,NAME,strlen(NAME));               //set name
        memory[NewIndex].content.fd.creat_t = curTime;
        memory[NewIndex].content.fd.access_t = curTime;
        memory[NewIndex].content.fd.mod_t = curTime;           //set the init access and mod time to the cur time since it was just modified, accessed and created at this instant
        
        memory[NewIndex].content.fd.access = 0644;          //default access
        memory[NewIndex].content.fd.owner = owner;
        memory[NewIndex].content.fd.size = strlen(inputData);
        
        bitvector[NewIndex] = 1;                    //mark bitvector as block is taken
        
        int FILEindexSlot = IndexNodeSearch(1,0);             //1 signifies what INDEX in memory to search through. 0 Is what to search FOR.
        
        memory[1].content.index[FILEindexSlot] = NewIndex;          //index holds array slot of new FILE node
        memory[1].NumIndices++;             //increment our counter to know # of indices

        
        
        
        int dataIndex = emptyIndexSearch();                 //find open block for data node

       
        //CREATING DATA NODE AND COPYING DATA INTO 'STORAGE'
        memory[dataIndex].type = DATA;                               //set type to data
        
        memory[NewIndex].content.fd.block_ref = dataIndex;        //refer file block ref to the new data node
        
        strncpy(memory[memory[NewIndex].content.fd.block_ref].content.data,inputData,strlen(inputData));           //copy data passed, into file
        
         bitvector[dataIndex] = 1;
        
        //we don't add the data node into the index node's index. Not needed
    }
}






void createDirectory(char NAME[MAX_NAME_LENGTH], unsigned short owner){

    int NewIndex = emptyIndexSearch();
    
    if (NewIndex == 0){
        printf("\nNo Empty spot in memory to create new Directory: %s\n", NAME);
        
    } else {
    
    unsigned long curTime = time(NULL);             // getting the epoch time in ms, which can be easily converted to Human time/date
    
    memory[NewIndex].type = DIR;                        //setting type to Directory
    
    strncpy(memory[NewIndex].content.fd.name,NAME,strlen(NAME));             //set name
    memory[NewIndex].content.fd.creat_t = curTime;
    memory[NewIndex].content.fd.access_t = curTime;
    memory[NewIndex].content.fd.mod_t = curTime;           //set the init access and mod time to the cur time
        
    memory[NewIndex].content.fd.access = 0755;
    memory[NewIndex].content.fd.owner = owner;
    memory[NewIndex].content.fd.size = 0;               // in 1-d system directory doesn't have size because it contains no files.
        
    memory[NewIndex].content.fd.block_ref = 1;      //points back to its original index node, Because its one dimensional, But this does make a cycle.
    
    bitvector[NewIndex] = 1;                    //mark bitvect as this block taken
    
        int indexSlot = IndexNodeSearch(1,0);             //1 signifies where in memory the index to search through. Trying to generalize for heirarchical structure later
        
        memory[1].content.index[indexSlot] = NewIndex;          //index holds array slot of new DIR
        
        memory[1].NumIndices++;             //increment our counter to know # of indices
    }
}





void deleteFile(char NAME[MAX_NAME_LENGTH]){

    int searchIndex = nodeSearch(NAME);
    
    if (searchIndex == -1){
        printf("\nCannot Delete! File %s Does NOT exist!\n", NAME);
        
    } else {
        
        memory[searchIndex].type = DELETED;             //setting type to DELETED
        
        for (int w = 0; w < MAX_NAME_LENGTH; w++) {
            memory[searchIndex].content.fd.name[w] = 0;         //set name to NULL
        }

        memory[searchIndex].content.fd.creat_t = 0;
        memory[searchIndex].content.fd.access_t = 0;
        memory[searchIndex].content.fd.mod_t = 0;           //set the init access and mod time to 0
        
        memory[searchIndex].content.fd.access = 0;
        memory[searchIndex].content.fd.owner = 0;
        memory[searchIndex].content.fd.size = 0;
        
        bitvector[searchIndex] = 0;                    //mark bitvector as block is free
        
        int delindex = IndexNodeSearch(1,searchIndex);     //search INDEX in memory[1] for searchIndex
        
        memory[1].content.index[delindex] = 0;
        
        shiftEverythingDown(delindex);
        
        memory[1].NumIndices--;             //increment our counter to know # of indices
        
        
        
        memory[memory[searchIndex].content.fd.block_ref].type = DELETED;                               //set type for DATA node to DELETED
        
        bitvector[memory[searchIndex].content.fd.block_ref] = 0;         //set bitvector to 0
        
        for (int y = 0; y < DATA_SIZE; y++) {
            memory[memory[searchIndex].content.fd.block_ref].content.data[y] = 0;         //set data to NULL
        }

        memory[searchIndex].content.fd.block_ref = 0;        //refer file block ref to 0
        
    }
}





void deleteDirectory(char NAME[MAX_NAME_LENGTH]){

    int searchIndex = nodeSearch(NAME);

    if (searchIndex == -1) {
        printf("\nCannot Delete! Directory %s Does NOT exist!\n", NAME);
        
    } else {
    
        memory[searchIndex].type = DELETED;                        //setting type to DELETED
        
        for (int w = 0; w < MAX_NAME_LENGTH; w++) {
            memory[searchIndex].content.fd.name[w] = 0;         //set name to NULL
        }
        
        memory[searchIndex].content.fd.creat_t = 0;
        memory[searchIndex].content.fd.access_t = 0;
        memory[searchIndex].content.fd.mod_t = 0;           //set init access and mod time to the 0
        
        memory[searchIndex].content.fd.access = 0;
        memory[searchIndex].content.fd.owner = 0;
        memory[searchIndex].content.fd.size = 0;
        
        memory[searchIndex].content.fd.block_ref = 0;      //points back to 0
        
        bitvector[searchIndex] = 0;                    //mark bitvect as this block taken
        
        int delindex = IndexNodeSearch(1,searchIndex);     //search INDEX in memory[1] for searchIndex
        
        memory[1].content.index[delindex] = 0;          //index holds array slot of new DIR
        
        shiftEverythingDown(delindex);
        
        memory[1].NumIndices--;
    
    
    
    }
}





int nodeSearch(char NAME[MAX_NAME_LENGTH]){

    for (int q = 1; q < NUM_BLOCKS ; q++) {
     
        if (strncmp(memory[q].content.fd.name,NAME,strlen(NAME)) == 0) {
            return q;
        }
    }

    return -1;
}





void shiftEverythingDown(int deletedSpot){      //starting at the index given(deleted spot) shift everything to the right, down one spot


    for (int z = deletedSpot; z < (INDEX_SIZE-1) ; z++) {
        memory[1].content.index[z] = memory[1].content.index[z+1];
        
    }
}





void printMemoryContents(){

    printf("\n\nMEMORY:\n");
    
    printf("Block\tType\tName\tSize\tOwner\tBlock_Ref\tContents\n");

    for(int i = 0; i < NUM_BLOCKS; i++){                //Loop through all blocks in memory
    
        if (bitvector[i] == 1) {

            if(memory[i].type == 0){                        //if Directory
            printf("%d:\tDIR:\t%s\t %d\t%d\t%hu\n", i, memory[i].content.fd.name, memory[i].content.fd.size,memory[i].content.fd.owner, memory[i].content.fd.block_ref);
            }
            
            if(memory[i].type == 1){                        //if File
                printf("%d:\tFILE:\t%s\t %d\t%d\t%hu\t\n", i, memory[i].content.fd.name, memory[i].content.fd.size, memory[i].content.fd.owner, memory[i].content.fd.block_ref);
            }
            
            if(memory[i].type == 2){                        //if INDEX
                printf("%d:\tINDEX:\t\t %d\t%d\t\t\t", i, memory[1].NumIndices, memory[i].content.fd.owner);
                
                for (int x = 0; x < memory[1].NumIndices; x++) {
                    printf("%hu, ",memory[1].content.index[x]);
                }
                printf("\n");
            }
            
            if(memory[i].type == 3){                        //if DATA
                printf("%d:\tDATA:\t\t\t\t\t\t%s\n", i, memory[i].content.data);
            }
            
            
        }
    }
            printf("\n");
}






void initialize(){

    
	createFS();                                 //malloc memory array and bitvector array
    
    
    
    //create superblock
    
    unsigned long curTime = time(NULL);     // getting the epoch time, which can be easily converted to Human time/date
    
    memory[0].type = 0;                     //setting superblock type to Directory
    
    strncpy(memory[0].content.fd.name,"/",1);               //set name
    memory[0].content.fd.creat_t = 0;
    memory[0].content.fd.access_t = curTime;
    memory[0].content.fd.mod_t = curTime;           //set the init access and mod time to the cur time
    
    memory[0].content.fd.access = 0400;             //default
    memory[0].content.fd.owner = 0;
    memory[0].content.fd.size = 0;
    
    bitvector[0] = 1;       //mark bitvector as this block taken
    
    //end create superblock
    
    
    
    
    
    
    
    //create 'super' index node
    
    memory[1].type = INDEX;
    
    memory[0].content.fd.block_ref = 1;         //link superblock's block ref to point to index node which is in slot 1 of memory
    
    //since their is no files in memory at this point, the index is left as is. updated when files/directories are added.
    bitvector[1] = 1;
    
    memory[1].NumIndices = 0;
    
    for(int j = 0; j<INDEX_SIZE; j++){
        memory[1].content.index[j] = 0;             //initialize index array to 0
    }
    //end create index node
}



int emptyIndexSearch(){                      //using the first empty block in memory found
    
    for(int i = 1; i < NUM_BLOCKS; i++){
    
        if(bitvector[i] == 0){
            return i;
        }
    }
    return 0;
}




int IndexNodeSearch(int indexSNum, int searchFor){              //using the first empty block in INDEX found
    
    for(int i = 0; i < INDEX_SIZE; i++){
        
        if(memory[indexSNum].content.index[i] == searchFor){
            return i;
        }
    }
    return 0;
}




void open(){

//check to see if file is in open file table
    
//if not, add it to open file table
    //by hashing its name to a spot thats calculated for

//adjust and update local and global openfile process tables
    
//if no reference counter exists for this file create reference counter
//increment reference counter between all processes
    
 //update access time
    
}

void read(){

//open

//confirm accurate permissions for users
    
//copy data from respective data node
//display read data
    
//update access time

}

void write(){
    
 //open
//confirm accurate permissions for user

//append to end of file, or overwrite over data to respective data node
    
//adjust last modified time
    
//update access time

}

void close(){

//make sure reference counter = 1, because issues can occur if we close file that is opened by mult processes

//close all connections
//remove file from open file tables
//update access time

}





int main(int argc, char *argv[]){

	initialize();

    printMemoryContents();
    
    createFile("Cool", 123, "This is data in a file");
    
    printMemoryContents();
    
	createDirectory("RandDir", 123);
    
    printMemoryContents();

    createDirectory("Ayyyy", 555);
    
    printMemoryContents();
    
    deleteDirectory("Ayyyy");
    
    printMemoryContents();
    
    deleteFile("Cool");

    printMemoryContents();

    createFile("Where", 8390, "More Data! Wooo!");
    
    printMemoryContents();

    createDirectory("What", 10196);

    printMemoryContents();
    
    free(memory);
    free(bitvector);
    
    return 0;
}
