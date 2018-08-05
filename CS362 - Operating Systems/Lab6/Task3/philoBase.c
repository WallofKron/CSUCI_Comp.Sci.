/*
 Robert Florence
 Lab6
 Task 3
 
 *  philosophers.c
 *  pthread_sync
 *  Created by AJ Bieszczad on 3/4/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define DEFAULT_NUM_OF_SEATS 5
#define DEFAULT_NUM_OF_TURNS 4

#define TRUE 1
#define DELAY ( (rand() % 5 + 1) * 1000)

typedef enum{ THINKING = 0, HUNGRY, EATING} STATE;
pthread_cond_t self[DEFAULT_NUM_OF_SEATS];
STATE state[DEFAULT_NUM_OF_SEATS];

void *philosopher (void *id);
void pickup(int id, int i);
void putdown(int id, int i);
void test(int i);

pthread_mutex_t *monitor_mutex;

int numOfSeats, numOfTurns;

int main (int argc, char **argv){
                                            // Just using A.J.'s default values for the seats/turns (5,4)
    numOfSeats = DEFAULT_NUM_OF_SEATS;
    numOfTurns = DEFAULT_NUM_OF_TURNS;
   
   monitor_mutex = calloc(numOfSeats, sizeof(pthread_mutex_t));
   
   // set the see for random number generator
   srand(time(NULL));
   
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
	printf ("Start a dinner for %d diners\n", numOfSeats );
   
	pthread_t philosopher_tid[numOfSeats];
   
	long i;
    
    for (int i = 0; i < numOfSeats; i++){
        state[i] = THINKING;
        pthread_cond_init(&self[i], NULL);
    }                                               //init condition
    
    
    for (i = 0; i < numOfSeats; i++){
		pthread_mutex_init (monitor_mutex + i, NULL);
    }                                                           //init mutex
    
    for (i = 0; i < numOfSeats; i++){
		pthread_create (&philosopher_tid[i], NULL, philosopher, (void *) i);
    }                                                                   //create the philosopher threads
    
    for (i = 0; i < numOfSeats; i++){
		pthread_join (philosopher_tid[i], NULL);
    }                                                           //wait for all threads to finish
    
    for (i = 0; i < numOfSeats; i++){
		pthread_mutex_destroy (monitor_mutex + i);
    }                                                           //destroy threads
    
	printf ("Dinner is no more.\n");
   
	return 0;
}

void *philosopher (void *num){
    
	int id = (long)num;
   
	printf ("Philsopher no. %d sits at the table.\n", id);
   // philosophers arrive at the table at various times
    
   usleep (DELAY);
    
	for (int i = 0; i < numOfTurns; i++){
        
        printf ("Philsopher no. %d gets hungry for the %d time!\n", id, i + 1);
      
        pickup(id, i);
        
        printf ("Philsopher no. %d eating\n", id);
               
        usleep (DELAY * 3);                 //eating delay
               
        printf ("Philsopher no. %d stopped eating\n", id);
               
        putdown(id, i);
       
        printf ("Philsopher no. %d finished turn %d\n", id, i + 1);

    }
   printf (">>>>>> Philsopher no. %d finished meal. <<<<<<\n", id);
    
   pthread_exit(NULL);
}

void pickup(int id, int i){
    
    while (TRUE) {
   
        printf ("Philsopher no. %d tries to grab both chopsticks\n", id);
        
        state[id] = HUNGRY;
        
        test(id);
    
        if (state[id] != EATING){
        
            pthread_cond_wait(&self[id], monitor_mutex);
        
        } else {
    
            break;
        }
    }
    printf ("Philsopher no. %d has grabbed chopsticks %d and %d\n", id, id, (id + 1) % numOfSeats);

}

void putdown(int id, int i){
    
    state[id] = THINKING;
    // test left and right neighbors
    test((id + (numOfSeats - 1)) % numOfSeats);
    test((id + 1) % numOfSeats);
    
    printf ("Philsopher no. %d has returned chopsticks %d and %d\n", id, id, ((id + 1)%numOfSeats));
}

void test(int id){

    if ((state[(id + (numOfSeats - 1)) % numOfSeats] != EATING) && (state[id] == HUNGRY) && (state[(id + 1) % numOfSeats] != EATING)){
        state[id] = EATING ;
        
        pthread_cond_signal(&self[id]);
    }
}
