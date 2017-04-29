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
	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void main()
{
 	uchar k,m=0x80;
	P0=0xff;
	P2=0x00;
	while(1)
	{
	 	for(k=0;k<8;k++)
		{
		 	m=_crol_(m,1);
			P2=m;
			P0=DSY_CODE[k+1];
			DelayMS(2);
		}
	}
}