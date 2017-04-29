#include <reg52.h>
#include <absacc.h>
#define uchar unsigned char
#define uint unsigned int
sbit LED = P1^0;
void main()
{
 	uint i;
	LED = 1;
	for(i=0;i<200;i++)
	{
	 	XBYTE[i]=i+1;
	}
	for(i=0;i<200;i++)
	{
	 	XBYTE[i+0x0100]=XBYTE[199-i];
	}
	LED=0;
	while(1);
}
