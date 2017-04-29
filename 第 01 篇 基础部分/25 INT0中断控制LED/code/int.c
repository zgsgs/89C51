#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit LED = P0^0;

void mian()
{
 	LED = 1;
	EA =1;
	EX0 = 1;
	TCON = 0x01;
	while(1);
}

void External_Interrupt_0() interrupt 0
{
 	LED = ~LED;
}