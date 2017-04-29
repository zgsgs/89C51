/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit CLK = P2^4;
sbit ST  = P2^5;
sbit EOC = P2^6;
sbit OE  = P2^7;
sbit PWM = P3^0;

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
 	uchar Val;
	TMOD = 0x02;
	TH0 = 0x14;
	TL0 = 0x00;
	IE  = 0x82;
	TR0 = 1;
	while(1)
	{
	 	ST = 0;
		ST = 1;
		ST = 0;
		while(!EOC);
		OE  = 1;
		Val = P1;
		OE  = 0;
		if(Val == 0)
		{
		 	PWM = 0;
			DelayMS(0xff);
			continue;
		}
		if(Val == 0xff)
		{
		 	PWM = 1;
			DelayMS(0xff);
			continue;
		}
		PWM = 1;
		DelayMS(Val);
		PWM = 0;
		DelayMS(0xff - Val);
	}
}

void Timer0_INT() interrupt 1
{
 	CLK = !CLK;
}