#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0x82,0xf8,0x80,0x90,0xff	
};

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	for(t=120;t>0;t--);
}

void main()
{
 	uchar i=0;
	P0=0x00;
	while(1)
	{
	 	P0=~DSY_CODE[i];
		i=(i+1)%10;/*œ‘ æ0-9*/
		DelayMS(200);
	}
}