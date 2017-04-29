#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

void DelayMS(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=200;i>0;i--);
	}
}

void Move_LED()
{
 	if((P1 &= 0x10)==0)	P0 = _cror_(P0,1);
	else if((P1 &= 0x20)==0)	P0 = _crol_(P0,1);
	else if((P1 &= 0x40)==0)	P2 = _cror_(P2,1);
	else if((P1 &= 0x80)==0)	P2 = _crol_(P2,1);
}

void main()
{
 	uchar Recent_Key=0xff;
	P0=0xfe;
	P1=0xfe;
	P2=0xfe;
	while(1)
	{
	 	if(Recent_Key != P1)
		{
		 	Recent_Key=P1;
			Move_LED();
			DelayMS(10);
		}
	}
}