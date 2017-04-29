#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit LED1 = P0^0; 
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit K1 = P1^0;
sbit K2 = P1^1;
sbit K3 = P1^2;
sbit K4 = P1^3;

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void main()
{
 	P0=0xff;
	P1=0xff;
	while(1)
	{
	 	LED1 = K1;
		LED2 = K2;
		if(K3==0)
		{
		 	while(K3==0)
			{
			 	LED3=~LED3;
			}
		}
		if(K4==0)
		{
		 	while(K4==0)
			{
			 	LED4=~LED4;
			}
		}
		DelayMS(10);
	}
}
