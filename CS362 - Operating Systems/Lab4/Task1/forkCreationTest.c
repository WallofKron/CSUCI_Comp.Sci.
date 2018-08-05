#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NFORKS 10

void do_nothing() {
	int i;
	i= 0;
}

int main(int argc, char *argv[]) {
	int pid, j, status;
	
	time_t t = time(NULL);
	printf("Start time: %s\n", ctime(&t));
	
	for (j=0; j<NFORKS; j++) {
		
		/*** error handling ***/
		if ((pid = fork()) < 0 ) {
			printf ("fork failed with error code= %d\n", pid);
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
	t = time(NULL);
	printf("End time: %s\n", ctime(&t));
}  
