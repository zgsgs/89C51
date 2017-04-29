#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};

void DelayMS(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=200;i>0;i--);
	}
}

void main()
{
 	uchar i,k=0x80;
	while(1)
	{
	 	for(i=8;i>0;i--)
		{
		 	P2=0xff;
			k=_crol_(k,1);
			P0=DSY_CODE[8-i];
			P2=k;
			DelayMS(3);
		}
	}
}

