#include	<stdio.h>
#include	<unistd.h>

int main(int argc, char *argv[]){
   int i = 0;
  /* while (i == 0){
      ;
}*/
   printf("Process %s pid is: %d\n", argv[1], getpid());
return 0;
}
