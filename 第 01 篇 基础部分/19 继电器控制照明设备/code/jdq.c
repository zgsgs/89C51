#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit K1 = P1^0;
sbit RELAY = P2^4;
void DelayMS(uint ms)
{
 	uchar t;
	while(ms--)
	{
	 	for(t=0;t<120;t++);
	}
}

void main()
{
 	P1 = 0xff;
	RELAY = 1;
	while(1)
	{
	 	if(K1==0)
		{
		 	while(K1==0);
			RELAY = ~RELAY;
			DelayMS(20);
		}
	}
}