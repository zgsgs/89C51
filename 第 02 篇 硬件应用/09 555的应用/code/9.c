/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit Signal = P1^0;
sbit BEEP = P3^7;

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	while(1)
	{
	 	if(Signal)
		{
			BEEP=~BEEP;
			Delay(3);	
		}
	}
}