/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P0^0;
sbit LED2 = P0^3;

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
 	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	PCON = 0x00;
	RI = 0;
	TR1 = 1;
	LED1 = LED2 =1;
	while(1)
	{
	 	if(RI)
		{
		 	RI = 0;
			switch(SBUF)
			{
			 	case 'A': LED1=~LED1;LED2=1;break;
				case 'B': LED2=~LED2;LED1=1;break;
				case 'C': LED1=~LED1;LED2=LED1;
			}
		}
		else 
			LED1=LED2=1;
		Delay(100);
	}
}