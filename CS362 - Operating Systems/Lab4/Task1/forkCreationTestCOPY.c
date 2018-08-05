#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define NFORKS 1000

void do_nothing() {
	int i;
    i = 0;
    //printf("%d! ",i);
}

int main(int argc, char *argv[]) {
	int pid, j, status;
	
    FILE *outputFileFork;
    outputFileFork = fopen("outputfileFORK.txt", "a");

    
    time_t currentt;
    struct timeval begtime;
    
    
    gettimeofday(&begtime,NULL);
    currentt = begtime.tv_usec;
    	
	for (j=0; j<NFORKS; j++) {
		
		/*** error handling ***/
		if ((pid = fork()) < 0 ) {
			fprintf (outputFileFork, "fork failed with error code= %d\n", pid);
			exit(0);
		}
		
		/*** this is the child of the fork ***/
		else if (pid ==0) {
			do_nothing();
			exit(0);
		}
		
		/*** this is the parent of the fork ***/
		else {
			waitpid(pid, &status, 0);
		}
	}
    time_t latert;

    struct timeval endtime;
    
    gettimeofday(&endtime,NULL);
    latert = endtime.tv_usec;

    fprintf(outputFileFork, "\nStart time(microseconds): %ld\n", currentt);

	fprintf(outputFileFork, "End time(microseconds): %ld\n", latert);
    
    unsigned long long elapsedtime = 1000 * (endtime.tv_sec - begtime.tv_sec) + (endtime.tv_usec - begtime.tv_usec) / 1000;
    fprintf(outputFileFork, "Process/FORK Time Taken: %llu\n\n\n", elapsedtime);
    printf("Results of speed test outputted to file 'outputfileFORK.txt'\n");

}
