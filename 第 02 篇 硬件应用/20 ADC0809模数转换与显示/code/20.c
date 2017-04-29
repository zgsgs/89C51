/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar code LEDData[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
sbit OE  = P1^0;
sbit EOC = P1^1;
sbit ST  = P1^2;
sbit CLK = P1^3;

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void Display_Result(uchar d)
{
 	P2 = 0xf7;
	P0 = LEDData[d%10];
	DelayMS(5);
	P2 = 0xfb;
	P0 = LEDData[d%100/10];
	DelayMS(5);
	P2 = 0xfd;
	P0 = LEDData[d/100];
	DelayMS(5);
}

void main()
{
 	TMOD = 0x02;
	TH0  = 0x14;
	TL0  = 0x00;
	IE   = 0x82;
	TR0  = 1;
	P1   = 0x3f;
	while(1)
	{
	 	ST = 0;
		ST = 1;
		ST = 0;
		while(EOC == 0);
		OE = 1;
		Display_Result(P3);
		OE = 0;
	}
}

void Timer0_INT() interrupt 1
{
 	CLK = !CLK;
}