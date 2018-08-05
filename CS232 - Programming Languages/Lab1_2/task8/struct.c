#include <stdio.h>
#include "person.h"

int main() {
    int employnum = 0;
    printf("How many employees?: ");
    scanf("%d", &employnum);
    
    PERSON *employees[employnum];
    
    for (int i=0; i < employnum; i++) {
        printf("Employee #: %d\n",i+1);
        add(employees[i]);
        
    }
    for (int i=0; i < employnum; i++) {
        printf("\nEmployee #: %d\n\n",i+1);
        printf("Age: %d\n", employees[i]->age);
        printf("Height: %d\n", employees[i]->height);
        printf("Name: %s\n", employees[i]->name);
        
    }
}