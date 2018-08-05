/*
 *  arrays.c
 *
 *  Created by AJ Bieszczad on 3/12/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include "arrays.h"

void arraycpy(int to[], int from[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      to[i] = from[i];
}

BOOLEAN lessOrSame(int a[], int b[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      if (a[i] > b[i])
         return FALSE;
   return TRUE;
}

void add(int a[], int b[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      a[i] += b[i];
}

void sub(int a[], int b[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      a[i] -= b[i];
}

void sub2(int a[], int b[], int c[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      a[i] = b[i] - c[i];
}

void set(BOOLEAN b, int a[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      a[i] = b;
}

BOOLEAN allTrue(BOOLEAN a[], int num)
{
   int i;
   for (i = 0; i < num; i++)
      if (a[i] != TRUE)
         return FALSE;
   return TRUE;
}

void display(int array[], int num)
{
   printf("[");
   int i;
   for (i = 0; i < num; i++)
      printf("%d ", array[i]);
   printf("]");
}

