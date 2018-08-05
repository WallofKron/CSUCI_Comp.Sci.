/*
 *  replace.h
 *  replace
 *  Created by AJ Bieszczad on 4/9/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 */

#ifndef DEBUGLEVEL
#define DEBUGLEVEL 3
#endif // DEBUGLEVEL

#ifndef _REPLACE_H
#define _REPLACE_H

#define oops(msg, errcode) { perror(msg); exit(errcode); }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int testLRU(int, int[], int);
int testOPT(int, int[], int);

#endif // _REPLACE_H
