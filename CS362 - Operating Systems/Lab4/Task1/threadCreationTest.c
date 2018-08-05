#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NTHREADS 10

void *do_nothing(void *null) {
	int i;
	i=0;
	pthread_exit(NULL);
}                      

int main(int argc, char *argv[]) {
	int rc, j;
	pthread_t tid;
	pthread_attr_t attr;
	
	time_t t = time(NULL);
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	printf("Start time: %s\n", ctime(&t));
			
	for (j=0; j<NTHREADS; j++) {
		rc = pthread_create(&tid, &attr, do_nothing, NULL);
		if (rc) {              
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
		
		/* Wait for the thread */
		rc = pthread_join(tid, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}
	
	t = time(NULL);
	printf("End time: %s\n", ctime(&t));
	
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	
}