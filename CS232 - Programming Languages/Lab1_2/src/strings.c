#include <stdio.h>

main()
{
    char msg[10];          /* array of 10 chars */
    char *p;               /* pointer to a char */
    char msg2[] = "Hello"; /* msg2 = 'H''e''l''l''o''\0' */

    // msg = "Bonjour"; /* ERROR. msg has a const address.*/
    p = "Bonjour"; /* address of “Bonjour” goes into p */

    // msg = p; /* ERROR. Message has a constant address. */
    /* cannot change it. */

    p = msg; /* OK */

    p[0] = 'H', p[1] = 'i', p[2] = '\0';
    /* *p and msg are now “Hi” */
}
