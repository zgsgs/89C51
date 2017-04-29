#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar i=0;
sbit SPK = P3^4;
sbit K1 = P1^0;
uchar code HI_LIST[]=
{
 	0,266,229,232,233,236,238,240,241,242,244,245,246,247,248
};
uchar code LO_LIST[]=
{
 	0,4,13,10,20,3,8,6,2,23,5,26,1,4,3
};

void T0_INT() interrupt 1
{
 	TL0 = LO_LIST[i];
	TH0 = HI_LIST[i];
	SPK = !SPK;
}

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
 	IE = 0x82;
	TMOD = 0x00;
	while(1)
	{
	 	while(K1==1);
		while(K1==0);
		for(i=1;i<15;i++)
		{
		 	TR0 = 1;
			DelayMS(500);
			TR0 = 0;
			DelayMS(50);
		}
	}
}