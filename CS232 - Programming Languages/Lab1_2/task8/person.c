//  person.c
//  Created by Florence, Robert on 2/4/16.

#include "person.h"
#include <stdio.h>

void add(PERSON *employee);


void add(PERSON *employee){
    
    printf("Age?: ");
    scanf("%d \n", &(employee->age));
    
    printf("Name?: ");
    scanf("%s \n", (employee->name));
    
    printf("Height?: ");
    scanf("%d \n", &(employee->height));
}
