/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <absacc.h>
#define uint unsigned int
#define uchar unsigned char
#define DAC0832 XBYTE[0xfffe]

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	uchar i;
	while(1)
	{
	 	for(i=0;i<256;i++)
		DAC0832 = i;
		DelayMS(1);
	}
}