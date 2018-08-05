/*
 *  bank.h
 *
 *  Created by AJ Bieszczad on 3/11/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#ifndef __BANK_H_
#define __BANK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include "arrays.h"

#define oops(errmsg, errnum) { perror(errmsg); exit(errnum); }

void initBank(int[], int, int);
void addBankCustomer(int, int[]);
void displayBankState();
BOOLEAN borrow(int, int[]);
BOOLEAN repay(int, int[]);

#endif