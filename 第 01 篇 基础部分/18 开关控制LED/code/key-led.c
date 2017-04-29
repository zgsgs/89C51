#include <reg52.h>
sbit S1 = P1^0;
sbit S2 = P1^1;
sbit LED1 = P0^0;
sbit LED2 = P0^1;

void main()
{
 	while(1)
	{
	 	LED1 = S1;
		LED2 = S2;
	}
}