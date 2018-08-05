//  person.h
//  Created by Florence, Robert on 2/4/16.

#ifndef _person_h
#define _person_h

#include <stdio.h>
#include <stdlib.h>

void add();

typedef char NAME[41];

typedef struct date{
    int month;
    int day;
    int year;
    
} DATE;

typedef struct person{
    NAME name;
    int age;
    int height;
    DATE bday;
    
} PERSON;

#endif
