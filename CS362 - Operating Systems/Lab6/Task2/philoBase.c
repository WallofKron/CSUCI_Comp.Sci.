/*
 Robert Florence
 Lab6
 Task 1
 
 *  philosophers.c
 *  pthread_sync
 *  Created by AJ Bieszczad on 3/4/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
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

void *philosopher (void *id);

pthread_mutex_t *chopstick;

int numOfSeats, numOfTurns;

int main (int argc, char **argv)
{
   if (argc < 3)
   {
      printf("\nUsage: philosophers <number of seats> <number of turns>\n");
      return 1;      
   }
   
   numOfSeats = atoi(argv[1]);
   numOfTurns = atoi(argv[2]);
   
   chopstick = calloc(numOfSeats, sizeof(pthread_mutex_t));
   
   // set the see for random number generator
   srand(time(NULL));
   
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
	printf ("Start a dinner for %d diners\n", numOfSeats );
   
	pthread_t philosopher_tid[numOfSeats];
   
	long i;
    
	for (i = 0; i < numOfSeats; i++)
		pthread_mutex_init (chopstick + i, NULL);
   
	for (i = 0; i < numOfSeats; i++)
		pthread_create (&philosopher_tid[i], NULL, philosopher, (void *) i);
   
	for (i = 0; i < numOfSeats; i++)
		pthread_join (philosopher_tid[i], NULL);
   
	for (i = 0; i < numOfSeats; i++)
		pthread_mutex_destroy (chopstick + i);
   
	printf ("Dinner is no more.\n");
   
	return 0;
}

void *philosopher (void *num)
{
	int id = (long)num;
   
	printf ("Philsopher no. %d sits at the table.\n", id);
   
   // philosophers arrive at the table at various times
   usleep (DELAY);
   
	int i;
    
	for (i = 0; i < numOfTurns; i++){
        
      printf ("Philsopher no. %d gets hungry for the %d time!\n", id, i + 1);
      printf ("Philsopher no. %d tries to grab chopstick %d\n", id, id);
        
        //int j = 0;                    used for testing
        
       while (TRUE) {
           
           while(pthread_mutex_trylock(&(chopstick[id])) != 0){
               
               /*printf("%d\n",j);              // used for spinning test
               j++;
               */
           ;                        //while the first chopstick is not grabbable, spin
           }
                                    //when it breaks out of first loop it has first chopstick
           
           printf ("Philsopher no. %d has grabbed chopstick %d\n", id, id);
           printf ("Philsopher no. %d tries to grab chopstick %d\n", id, (id+1) % numOfSeats);

           if (pthread_mutex_trylock(&(chopstick[(id+1) % numOfSeats])) != 0){
               
               pthread_mutex_unlock(&(chopstick[id]));         //if second chopstick not avail
               pthread_mutex_unlock(&(chopstick[(id+1) % numOfSeats]));        //put down both

               printf ("Philsopher no. %d: chopstick %d not available\n", id, (id+1)% numOfSeats);

               printf ("Philsopher no. %d has returned chopstick %d\n", id, id);

               usleep(DELAY);           //sleep

           } else {                                     //second chopstick was avail. Eat!
           
               printf ("Philsopher no. %d grabbed chopstick %d\n", id, (id+1) % numOfSeats);
               // YEEEAAAAH !!!
               printf ("Philsopher no. %d eating\n", id);
               
               usleep (DELAY * 3);
               
               printf ("Philsopher no. %d stopped eating\n", id);
               
               pthread_mutex_unlock(&(chopstick[id]));
               printf ("Philsopher no. %d has returned chopstick %d\n", id, id);

               pthread_mutex_unlock(&(chopstick[(id+1) % numOfSeats]));        //after eating, release both
               printf ("Philsopher no. %d has returned chopstick %d\n", id, (id+1) % numOfSeats);
               
               break;                       //break out of while(true)
           }
       }
      
      printf ("Philsopher no. %d finished turn %d\n", id, i + 1);
        //j=0;                      used for testing
    }

   printf (">>>>>> Philsopher no. %d finished meal. <<<<<<\n", id);
   
   pthread_exit(NULL);
}

