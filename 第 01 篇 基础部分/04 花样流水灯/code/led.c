#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code Pattern_P0[]=
{
 	0xfc,0xf9,0xf3,0xe7,0xcf,0x9f
};
uchar code Pattern_P2[]=
{
 	0xf5,0xf6,0xfe,0x54,0x56,0x76,0xd7,0x49,0xa9,0xe4,0xc6
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
 	uchar i;
	while(1)
	{
	 	for(i=136;i>0;i--)
		{
		 	P0=Pattern_P0[i];
			P1=Pattern_P2[i];
			DelayMS(150);
		}	
	}
}