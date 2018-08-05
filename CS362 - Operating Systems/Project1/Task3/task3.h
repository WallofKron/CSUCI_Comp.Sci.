/*
 Robert Florence
 Prof. A.J/Dolan-Stern
 CS362
 Project 1 Task3
 */

#ifndef __TASK3_H__
#define __TASK3_H__

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

#define BLOCK_SIZE 256
#define MAX_NAME_LENGTH 128
#define DATA_SIZE 254
#define INDEX_SIZE 127
#define NUM_BLOCKS 16


struct node *memory; // allocate 2^16 blocks (in init)

char *bitvector; // allocate space for managing 2^16 blocks (in init)



typedef char data_t;
typedef unsigned short index_t;



typedef enum{
    DIR = 0,
    File,
    INDEX,
    DATA,
    DELETED
} NODE_TYPE;



typedef struct fs_node{
   char name[MAX_NAME_LENGTH];
   time_t creat_t; // creation time
   time_t access_t; // last access
   time_t mod_t; // last modification
   mode_t access; // access rights for the file
   unsigned short owner; // owner ID
   unsigned short size;
   index_t block_ref; // reference to the data or index block
} FS_NODE;



typedef struct node{
   NODE_TYPE type;
    int NumIndices;
   union{
       
      FS_NODE fd;
      data_t data[DATA_SIZE];
      index_t index[INDEX_SIZE];
   
   } content;
} NODE;
// storage blocks




void initialize();

void createFS();

void createFile(char NAME[MAX_NAME_LENGTH],unsigned short owner, data_t data[DATA_SIZE]);
void createDirectory(char[MAX_NAME_LENGTH], unsigned short owner);

void deleteFile(char NAME[MAX_NAME_LENGTH]);
void deleteDirectory(char NAME[MAX_NAME_LENGTH]);

void printMemoryContents();

int emptyIndexSearch();
int IndexNodeSearch(int indexSNum, int searchFor);

int nodeSearch(char NAME[MAX_NAME_LENGTH]);

void shiftEverythingDown(int);

#endif
