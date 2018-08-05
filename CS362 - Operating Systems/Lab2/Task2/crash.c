#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct name
{
    char *first,
    char *last;
}NAME;

typedef NAME *NAME_PTR;

void get_name(NAME_PTR);

int main(void)
{
    NAME_PTR me;
    get_name(me);
    printf("Hello %s %s!\n", me->first, me->last);
}

void get_name(NAME_PTR ptr)
{
    printf("What's your first name?\n");
    scanf("%s", ptr->first);
    printf("What's your last name?\n");
    scanf("%s", ptr->last);
}
