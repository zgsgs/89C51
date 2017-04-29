#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90	
};
uchar code DSY_IDX[]=
{
 	0x01;0x02;0x04;0x08;0x10;0x20;0x40;0x80
}
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
 	uchar k,m;
	P0=0xff;
	P2=0x00;
	while(1)
	{
	 	for(k=0;k<30;k++)
		{
			for(m=0;m<8;m++)
			{
				P2=code DSY_IDX[k];
				P0=DSY_CODE[m];
				DelayMS(2);
			}
		}
		P2=0x00;
		DelayMS(1000);
	}
}