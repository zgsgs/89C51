#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit LED = P0^0;
uchar T_Count = 0;
void main()
{
 	TMOD = 0x00;
	TH0  = (8192-5000)/32;
	TL0  = (8192-5000)%32;
	IE   = 0x82;
	TR0  = 1;
	while(1);
}

void LED_Flash() interrupt 1
{
 	TH0 = (8192-5000)/32;
	TL0 = (8192-5000)%32;
	if(++T_Count == 100)
	{
	 	LED = !LED;
		T_Count = 0;
	}
}