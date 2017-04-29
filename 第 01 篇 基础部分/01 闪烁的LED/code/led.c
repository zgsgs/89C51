#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit LED = P1^0;

void DelayMS(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=120;i>0;i--);
	}
}

void main()
{
 	while(1)
	{
	 	LED = ~LED;
		DelayMS(150);
	}
}