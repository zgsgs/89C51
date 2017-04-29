/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit DIN = P2^0;
sbit CSB = P2^1;
sbit CLK = P2^2;
uchar Disp_Buffer[8]=
{
 	2,0,0,9,10,8,10,9
};
void DelayMS(uint x)
{
	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Write(uchar Addr,uchar Dat)
{
 	uchar i;
	CSB = 0;
	for(i=0;i<8;i++)
	{
	 	CLK = 0;
		Addr <<= 1;
		DIN	= CY;
		CLK = 1;
		_nop_();
		_nop_();
		CLK = 0;
	}
	for(i=0;i<8;i++)
	{
	 	CLK = 0;
		Dat <<= 1;
		DIN	= CY;
		CLK = 1;
		_nop_();
		_nop_();
		CLK = 0;	
	}
	CSB = 1;
}

void Initialise()
{
 	Write(0x09,0xff);
	Write(0x0a,0x07);
	Write(0x0b,0x07);
	Write(0x0c,0x01);
}

void main()
{
 	uchar i;
	Initialise();
	DelayMS(1);
  	for(i=0;i<8;i++)
	{
	 	Write(i+1,Disp_Buffer[i]);
	}
	while(1);
}