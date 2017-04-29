/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uint unsigned int
#define uchar unsigned char
sbit SPL = P2^5;

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
 	SCON = 0x10;
	while(1)
	{
	 	SPL = 0;
		SPL = 1;
		while(RI == 0);
		RI = 0;
		P0 = SBUF;
		Delay(20);
	}
}