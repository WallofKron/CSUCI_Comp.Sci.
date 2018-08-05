#include <stdio.h>

struct birthday{
    int month;
    int day;
    int year;
  };

int main() {
  struct birthday mybday;	/* - no ‘new’ needed ! */
 				/* then, it’s just like Java ! */
  scanf("%d/%d/%d", &mybday.month, &mybday.day, &mybday.year);
  printf("I was born on %d/%d/%d\n", mybday.month, mybday.day, mybday.year);
}
