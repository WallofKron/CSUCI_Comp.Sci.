#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define Numthreads 3

typedef enum {
    PRIORITY_HIGH = 99,
    PRIORITY_MEDIUM = 50,
    PRIORITY_LOW = 1
} PRIORITY;


void *do_nothing(void *null);

int main(int argc, char *argv[]) {
    int rc, j;

    pthread_t tid;
    pthread_attr_t attr;


for (j=0; j < Numthreads; j++) {
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
}

void *do_nothing(void *null) {
    int i;
    i=0;
    //printf("%d! ",i);
    pthread_exit(NULL);
}
