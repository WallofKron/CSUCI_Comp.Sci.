#ifndef __DISK_H
#define __DISK_H

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <time.h>
#include <signal.h>

#define COUNTDOWN_VALUE 40				// 20 for testing reading writing


#define SECT_SIZE 12                //changed for testing
#define NUM_OF_SECTS 128
#define NUM_OF_CYLS 200
#define NUM_OF_HEADS 10

#define MAX_LOGICAL_SECTOR 256000 // NUM_OF_HEADS * NUM_OF_CYLS * NUM_OF_SECTS


char disk[NUM_OF_HEADS][NUM_OF_CYLS][NUM_OF_SECTS][SECT_SIZE];      //simulated disk space 4d array


struct physaddr_t *physaddr;                //struct for the 4-d array


int choice = 0;

int logicBlockNum;
int NumSectors;
void *buff;

char writeStrng[SECT_SIZE * NUM_OF_SECTS] = {0};    //string for writing to disk. Max size is one whole cylinder. ex size of 12 for sect.  times the number of sects per cylinder.

int logicalAddress = 0;


timer_t gTimerid;
int count = COUNTDOWN_VALUE;



typedef char sector_t[SECT_SIZE];
typedef sector_t head_t[NUM_OF_SECTS];
typedef head_t cylinder_t[NUM_OF_HEADS];
typedef cylinder_t disk_t[NUM_OF_CYLS];


typedef struct physaddr_t{
  int cyl;
  int head;
  int sect;
} physaddr_t;



/**
This function translates a logical to a physical address.
**/
int log_to_phys(int logaddr, physaddr_t *phaddr);

/**
This function translates a physical to a logical address.
**/
int phys_to_log(physaddr_t *phaddr);

/**
This function copies num_of_sectors sectors from the disk to the buffer starting with sector pointed to by logical_block_num. You should validate the parameters before serving the request.
**/
int readBlock(int logical_block_num, int num_of_sectors, void **buffer);

/**
This function copies num_of_sectors sectors from the buffer to the disk starting at sector pointed to by logical_block_num. Here, you also should validate the parameters.
**/
int writeBlock(int logical_block_num, int num_of_sectors, void *buffer);



void timer_callback(int sig);
void stop_timer(void);
void start_timer(void);


char *randstring(size_t length);

#endif
