#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_Index[] = 
{
 	0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f
};
uchar code BCD_CODE[] =
{
 	2,0,0,9,10,8,10,7
};

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
 	uchar k;
	while(1);
	{
	 	for(k=0;k<8;k++)
		{
		 	P2 = DSY_Index[k];
			P0 = BCD_CODE[k];
			DelayMS(1);
		}
	}
}