#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar tc0 = 0,tc1 = 0; 

void main()
{
 	P0 = 0xfe;
	P2 = 0xfe;
	TMOD = 0x11;
	TH0  = (65535-15000)/256;
	TL0  = (65535-15000)%256;
	TH1  = (65535-15000)/256;
	TL1  = (65535-15000)%256;
	IE = 0x8a;
	TR0  = 1;
	TR1  = 1;
	while(1);
}

void Time0() interrupt 1
{
 	TH0  = (65535-15000)/256;
	TL0  = (65535-15000)%256;
	if(++tc0 == 10)
	{
	 	tc0 = 0;
		P0 = _crol_(P0,1);
	}
}

void Time1() interrupt 3
{
 	TH0  = (65535-15000)/256;
	TL0  = (65535-15000)%256;
	if(++tc1 == 10)
	{
	 	tc1 = 0;
		P2 = _crol_(P2,1);
	}
}