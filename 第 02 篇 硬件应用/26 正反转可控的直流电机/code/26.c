/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit K1   = P3^0;
sbit K2   = P3^1;
sbit K3   = P3^2;
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit MA   = P1^0;
sbit MB   = P1^1;

void main(void)
{
	LED1 = 1;
	LED2 = 1;
	LED3 = 0;
	while(1)
	{
	 	if(K1 == 0)
		{
		 	while(K1 == 0);
			LED1 = 0;
			LED2 = 1;
			LED3 = 1;
			MA   = 0;
			MB   = 1;
		}
		if(K2 == 0)
		{
		 	while(K1 == 0);
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			MA   = 1;
			MB   = 0;
		}
		if(K3 == 0)
		{
		 	while(K1 == 0);
			LED1 = 1;
			LED2 = 1;
			LED3 = 0;
			MA   = 0;
			MB   = 0;
		}
	}
}
