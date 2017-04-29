#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
uchar DSY_Buffer[3]={0,0,0};

void DelayMS(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}
void main()
{
 	uchar i,m,Num;
	P0 = 0xff;
	P2 = 0xff;
	while(1)
	{
	 	m = 0xfe;
		Num = P1;
		DSY_Buffer[0] = Num/100;
		DSY_Buffer[1] = Num/10%10;
		DSY_Buffer[2] = Num%10;
		for(i=0;i<3;i++)
		{
		 	m = _crol_(m,1);
			P2 = m;
			P0 = DSY_CODE[DSY_Buffer[i]];
			DelayMS(10);
		}
	}
}