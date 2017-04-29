/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
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
 	uchar c = 0x80;
	SCON = 0x00;
	TI = 1;
	while(1)
	{
	 	c = _crol_(c,1);
		SBUF = c;
		while(TI==0);
		TI = 0;
		Delay(400);
	}
}