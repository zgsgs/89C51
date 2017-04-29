#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit B1 = P0^0;
sbit G1 = P0^1;
sbit R1 = P0^2;
sbit Y1 = P0^3;
uint i,j,k;
void main()
{
 	i=j=k=0;
	P0 = 0xff;
	TMOD = 0x02;
	TH0 = 256-200;
	TL0 = 256-200;
	IE = 0x82;
	TR0 = 1;
	while(1);
}

void LED_Flash_and_Scroll() interrupt 1
{
 	if(++k<35) return;
	k = 0;
	switch(i)
	{
	 	case 0:B1=!B1;break;
		case 1:G1=!G1;break;
		case 2:R1=!R1;break;
		case 3:Y1=!Y1;break;
		default: i=0;
	}
	if(++j<300) return;
	j = 0;
	P0 = 0xff;
	i++;
}