#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct name
{
    char first[150];
    char last[150];
}NAME;

//typedef NAME *NAME_PTR;

void get_name(NAME *ptr);

int main(void)
{
//    int ARRAYSIZE = 150;
    NAME *me =(NAME*) malloc(sizeof(NAME));
    
    get_name(me);
    printf("Hello %s %s!\n", me->first, me->last);
}

void get_name(NAME *ptr)
{
    printf("What's your first name?\n");
    scanf("%s", ptr->first);
    printf("What's your last name?\n");
    scanf("%s", ptr->last);
}
