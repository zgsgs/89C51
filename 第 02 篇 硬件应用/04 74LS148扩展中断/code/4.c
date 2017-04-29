#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit LED = P1^0;
void EX_INT0() interrupt 0
{
 	uchar bi = P2 & 0x07;
	P0 = _cror_(0x7f,bi);
}

void main()
{
 	uint i;
	IE  = 0x81;
	IT0 = 0;
	while(1)
	{
	 	LED = !LED;
		for(i=0;i<30000;i++);
		if(INT0 == 1)
			P0 = 0xff;
	} 
}