#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90	
};

uchar Num[]=
{
 	10,10,10,10,10,10,10,10,2,9,8
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
 	uchar i,j,k,m;
	P0 = 0xff;
	P2 = 0x00;
	m  = 0x80;
	k  = 0;
	while(1)
	{
	 	for(i=0;i<15;i++)
		{
		 	for(j=0;j<8;j++)
			{
			 	m  = _crol_(m,1);
				P2 = m;
				P0 = DSY_CODE[Num[(k+j)%11]];
				DelayMS(2);
			}
		}	
		k = (k+1)%11;
	}
}