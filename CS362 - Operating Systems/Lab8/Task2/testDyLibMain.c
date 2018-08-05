 /*
 *  testDyLibMain.c
 *  lect09
 *
 *  Created by AJ Bieszczad on 3/16/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 * MODIFIED: 3/29/2010 to fix the comments on creating .so (must use -fPIC)
 *
 * TESTED on Ubuntu 10.4 and on Mac OS X 10.6.3
  
  
  Create a dynamic library as follows (assuming giveMeNum.c holds code for the library):
  
>  gcc -shared -fPIC -o libgiveMeNum.so giveMeNum.c

  If the following program is in a file named testDyLibMain.c, you build an executable 
  with the command:
  
>  gcc -rdynamic -o testDyLibMain testDyLibMain.c -ldl

  Then execute it with:

> ./testDyLibMain

  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
   void *dylibHandle;
   char *error;
   
   dylibHandle = dlopen ("./libgiveMeNum.so", RTLD_LAZY);
   if (!dylibHandle)
   {
      fprintf (stderr, "ERR: %s\n", dlerror());
      exit(1);
   }
   // clear any existing errors
   dlerror();
   
   int (*giveMeNum)() = dlsym(dylibHandle, "giveMeNum");
   int n = (*giveMeNum)();
   if ((error = dlerror()) != NULL)
   {
      fprintf (stderr, "ERR: %s\n", error);
      exit(1);
   }
   printf ("You gave me : %d\n", n);
   dlclose(dylibHandle);
   return 0;
}
