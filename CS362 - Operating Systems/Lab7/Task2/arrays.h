/*
 *  arrays.h
 *
 *  Created by AJ Bieszczad on 3/12/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#ifndef __ARRAYS_H_
#define __ARRAYS_H_

#include <stdio.h>

typedef int BOOLEAN;
#define TRUE 1
#define FALSE 0
#define NOT(x) (x == TRUE ? FALSE : TRUE)

void arraycpy(int[], int [], int);
BOOLEAN lessOrSame(int[], int[], int);
BOOLEAN allTrue(int[], int);
void display(int[], int);
void add(int[], int[], int);
void sub(int[], int[], int);
void sub2(int[], int[], int[], int);

#endif