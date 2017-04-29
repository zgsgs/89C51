/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <absacc.h>
#define uint unsigned int
#define uchar unsigned char
#define PA XBYTE[0x0000] 
#define PB XBYTE[0x0001]
#define PC XBYTE[0x0002]
#define COM XBYTE[0x0003]

uchar code DSY_CODE_Queue[]=
{
 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xa4,0xc0,0xc0,0x80,0xc0,0x80,0xf9,0x80,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

uchar code DSY_Index[]=
{
 	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};

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
 	uchar i,j,k;
	COM = 0x80;
	while(1)
	{
	 	for(j=0;j<40;j++)
		{
		 	for(k=0;k<8;k++)
			{
				PB = DSY_Index[k];
				PA = DSY_CODE_Queue[k+i];
				Delay(1);
			}
		}
		i = (i+1)%15;
	}
}