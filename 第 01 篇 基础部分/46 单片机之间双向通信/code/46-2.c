/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P1^0;
sbit LED2 = P1^3;
sbit K1 = P1^7;
uchar NumX = 0xff;
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
 	LED1=LED2=1;
	SCON = 0x50;
	TMOD = 0x20;
	PCON = 0x00;
	TH1  = 0xfd;
	TL1  = 0xfd;
	TI   = 0;
	RI   = 0;
	TR1  = 1;
	IE   = 0x90;
	while(1)
	{
	 	Delay(100);
		if(K1==0);
		{
		 	while(K1==0);
			NumX = (NumX+1)%11;
			SBUF = NumX;
			while(TI == 0);
			TI = 0;
		}
	}
}

void Serial_INT() interrupt 4
{
 	if(RI)
	{
	 	RI = 0;
		switch(SBUF)
		{
			case 'X': LED1=1;LED2=1;break;
			case 'A': LED1=0;LED2=1;break;
			case 'B': LED2=0;LED1=1;break;
			case 'C': LED1=0;LED2=0;
		}
	}
}
