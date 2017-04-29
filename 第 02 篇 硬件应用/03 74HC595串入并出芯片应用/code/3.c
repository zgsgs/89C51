/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit SH_CP = P2^0;
sbit DS    = P2^1;
sbit ST_CP = P2^2;
uchar temp;
uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90	
};

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void In_595()
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	temp <<= 1;
		DS   = CY;
		SH_CP = 1;
		_nop_();
		_nop_();
		SH_CP = 0;
	}
}

void Out_595()
{
 	ST_CP = 0;
	_nop_();
	ST_CP = 1;
	_nop_();
	ST_CP = 0;
}

void main()
{
 	uchar i;
	while(1)
	{
	 	for(i=0;i<10;i++)
		{
		 	temp = DSY_CODE[i];
			In_595();
			Out_595();
			Delay(200);
		}
	}
}