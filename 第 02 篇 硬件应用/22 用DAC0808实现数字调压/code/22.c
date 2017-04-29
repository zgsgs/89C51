/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit K1 = P3^0;
sbit K2 = P3^1;
sbit K3 = P3^2;
sbit K4 = P3^3;
sbit K5 = P3^4;
sbit K6 = P3^5;
sbit K7 = P3^6;
sbit K8 = P3^7;

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	P2 = 0x00;
	while(1)
	{
	 	if(K1 == 0) P2 = 0;
		if(K2 == 0) P2 = 35;
		if(K3 == 0) P2 = 70;
		if(K4 == 0) P2 = 105;
		if(K5 == 0) P2 = 140;
		if(K6 == 0) P2 = 175;
		if(K7 == 0) P2 = 210;
		if(K8 == 0) P2 = 255;
		DelayMS(2);
	}
}