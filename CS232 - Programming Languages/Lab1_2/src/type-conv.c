#include <stdio.h>

int main(void)
{
	int i,j = 12;      /* i not initialized, only j */
	float f1,f2 = 1.2;

	i = (int) f2;      /* explicit: i <- 1, 0.2 lost */
	f1 = i;            /* implicit: f1 <- 1.0 */

	f1 = f2 + (int) j; /* explicit: f1 <- 1.2 + 12.0 */
	f1 = f2 + j;       /* implicit: f1 <- 1.2 + 12.0 */
}
