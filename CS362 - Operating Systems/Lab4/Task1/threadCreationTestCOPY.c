#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


#define NTHREADS 1000

void *do_nothing(void *null) {
	int i;
	i=0;
    //printf("%d! ",i);
	pthread_exit(NULL);
}                      

int main(int argc, char *argv[]) {
	int rc, j;
    
    FILE *outputFileThread;
    outputFileThread = fopen("outputFileTHREAD.txt", "a");

    
	pthread_t tid;
	pthread_attr_t attr;
	
    time_t currentt;
    struct timeval begtime;
    
    
    gettimeofday(&begtime,NULL);
    currentt = begtime.tv_usec;
    
    fprintf(outputFileThread, "\nStart time(microseconds): %ld\n", currentt);
    
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
				
	for (j=0; j<NTHREADS; j++) {
		rc = pthread_create(&tid, &attr, do_nothing, NULL);
		if (rc) {              
			fprintf(outputFileThread, "ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
		
		/* Wait for the thread */
		rc = pthread_join(tid, NULL);
		if (rc) {
			fprintf(outputFileThread, "ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}
	
    time_t latert;
    
    struct timeval endtime;
    
    gettimeofday(&endtime,NULL);
    latert = endtime.tv_usec;
    
    
    fprintf(outputFileThread, "End time(microseconds): %ld\n", latert);
    
    unsigned long long elapsedtime = 1000 * (endtime.tv_sec - begtime.tv_sec) + (endtime.tv_usec - begtime.tv_usec) / 1000;
    fprintf(outputFileThread, "Thread Time Taken: %llu\n\n\n", elapsedtime);

    printf("Results of speed test outputted to file 'outputfileTHREAD.txt'\n");
    
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
}
