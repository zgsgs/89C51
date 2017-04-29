/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sfr WDRST = 0xA6;
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit K1   = P1^4;

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
 	LED1 = 0;
	LED2 = 1;
	DelayMS(2000);
	TMOD = 0x01;
	TH0  = -16000/256;
	TL0  = -16000%256;
	IE   = 0x82;
	WDRST = 0x1E;
	WDRST = 0xE1;
	while(1)
	{
	 	if(K1==0)
		{
		 	TR0 = 0;
			LED1 = 1;
			LED2 = ~LED2;
			DelayMS(200);
		}
	}
}

void Timer0() interrupt 1
{
 	TH0  = -16000/256;
	TL0  = -16000%256;
	WDRST = 0x1E;
	WDRST = 0xE1;	
}