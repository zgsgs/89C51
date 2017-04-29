#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

void DelayMS(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=120;i>0;i--);
	}
}

void main()
{
 	P0 = 0xFE;
	while(1)
	{
	 	P0 = _crol_(P0,1);		//左移函数
		DelayMS(150);
	}
}
