#include <stdio.h> 

void myproc (int d);
void mycaller(void (* f)(int), int param);

int main(void) { 
	myproc(10);		/* call myproc with parameter 10*/
	mycaller(myproc, 10); /* and do the same again ! */
} 

void mycaller(void (* f)(int), int param){
	(*f)(param); 	/* call function *f with param */ 
}

void myproc (int d){
 	/* do something with d */
}
