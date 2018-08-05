#include	<errno.h>
#include	<sys/types.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/wait.h>
#define oops(m) ({fprintf(stderr, "ERROR: %s\n", m); exit(-1);})
int main(){
	const int leftchild = 1;
	const int rightchild = 2;
	pid_t pid;
	int root = getpid();
	
	if (pid = fork()) {
		if (pid = fork()) {
		} 
	} 
		
		printf("%d\n",getpid());


	if (pid < 0){ 				/* error occurred */
		oops("Fork Failed!");
   	}



	else if (pid == 0){ 				/* child process */
		
		
		if(getpid()-root == leftchild || getpid()-root == rightchild){
			
			if (pid = fork()) {
		if (pid = fork()) {
			} 
		} 
		
		printf("I am the child %d\n",getpid());

				
	} else {

		printf("I am the child %d\n",getpid());

		if (execlp("./iam","iam", "Hello Parent!!",NULL) < 0){

		   oops("Execlp Failed!");
		}
	}
	
	} else { 					/* parent process */
		printf("I am the parent %d\n",getpid());
		
      if (wait(NULL) < 0){

         printf("-1 from wait(NULL) with errno = %d\n", errno);

		}
		
		printf("Child Complete\n");
		exit(0);
	
	}
}
