#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit Key = P1^7;
sbit DoorBell = P3^0;
uint p = 0;

void Timer0() interrupt 1
{
 	DoorBell = ~DoorBell;
	p++;
	if(p<400)
	{
	 	TH0 = (8192-700)/32;
		TL0 = (8192-700)%32;
	}
	else if(p<800)
	{
	 	TH0 = (8192-1000)/32;
		TL0 = (8192-1000)%32;
	}
	else 
	{
	 	TR0 = 0;
		P = 0;
	}
}

void main()
{
 	IE = 0x82;
	TMOD = 0x00;
	TH0 = (8192-700)/32;
	TL0 = (8192-700)%32;
	while(1)
	{
	 	if(Key == 0)
		{
		 	TR0 = 1;
			while(Key==0);
		}
	}
}