/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit SPK = P3^7;
uchar FRQ = 0x00;

void Delayms(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	P2 = 0x00;
	TMOD = 0x11;
	TH0 = 0x00;
	TL0 = 0xff;
	IT0 = 1;
	IE = 0x8b;
	IP = 0x01;
	TR0 = 0;
	TR1 = 0;
	while(1)
	{
	 	FRQ++;
		Delayms(1);
	}
}

void EX0_INT() interrupt 0
{
 	TR0 = !TR0;
	TR1 = !TR1;
	if(P2 == 0x00)
		P2 = 0xe0;
	else 
		P2 = 0x00;
}

void T0_INT() interrupt 1
{
 	TH0 = 0xfe;
	TL0 = FRQ;
	SPK = ~SPK;
}

void T1_INT() interrupt 3
{
 	TH0 = -45000/256;
	TL0 = -45000%256;
	P2 = _crol_(P2,1);
}