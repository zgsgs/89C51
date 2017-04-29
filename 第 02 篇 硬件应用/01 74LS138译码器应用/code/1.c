/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

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
 	P2 = 0x00;
	while(1)
	{
	 	P2 = (P2+1)%8;
		Delay(50);
	}
}