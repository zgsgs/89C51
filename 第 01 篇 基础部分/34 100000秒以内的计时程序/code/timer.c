#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar Count;
sbit Dot = P0^7;
uchar code DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

uchar Digits_of_6DSY[]={0,0,0,0,0,0};

void DelayMS(uint x)
{
 	uchar i;
	while(--x)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	uchar i,j;
	P0 = 0x00;
	P3 = 0xff;
	Count =0;
	TMOD = 0x01;
	TH0  = (65535-50000)/256;
	TL0  = (65535-50000)%256;
	IE = 0x82;
	TR0 = 1;
	while(1)
	{
	 	j = 0x7f;
		for(i=5;i!=-1;i--)
		{
		 	j=_crol_(j,1);
			P3 = j;
			P0 = DSY_CODE[Digits_of_6DSY[i]];
			if(i==1) P0 |= 0x80;
			DelayMS(2);
		}
	}
}

void Time0() interrupt 1
{
 	uchar i;
	TH0  = (65535-50000)/256;
	TL0  = (65535-50000)%256;
	if(++Count !=2) return;
	Count = 0;
	Digits_of_6DSY[0]++;
	for(i=0;i<=5;i++)
	{
	 	if(Digits_of_6DSY[i] == 10)
		{
		 	Digits_of_6DSY[i] = 0;
			if(i != 5) Digits_of_6DSY[i+1]++;
		}
		else break;
	}
}