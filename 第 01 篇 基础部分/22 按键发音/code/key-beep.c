#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit BEEP = P3^7;
sbit K1   = P1^4;
sbit K2   = P1^5;
sbit K3   = P1^6;
sbit K4   = P1^7;

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Play(uchar t)
{
 	uchar i;
	for(i=0;i<100;i++)
	{
	 	BEEP = ~BEEP;
		DelayMS(t);
	}
	BEEP = 0;
}

void main()
{
 	P1 = 0xff;
	while(1)
	{
	 	if(K1==0) Play(1);
		if(K2==0) Play(2);
		if(K3==0) Play(3);
		if(K4==0) Play(4);
	}
}