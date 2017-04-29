#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
uchar Count = 0;

void main()
{
 	P0 = 0x00;
	P2 = 0x00;
	TMOD = 0x06;
	TH0=255;
	TL0=255;
	ET0=1;
	EX0=1;
	EA =1;
	IP =0x02;
	IT0=1;
	TR0=1;
	while(1)
	{
	 	P0 = DSY_CODE[Count/10];
		P2 = DSY_CODE[Count%10];
	}
}

void Clear_Counter() interrupt 0
{
 	Count = 0;
}

void Key_Counter() interrupt 1
{
 	Count = (Count + 1) %100;
}