#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit K1 = P3^7;
uchar i,Second_Counts,Key_Flag_Idx;
bit Key_State;
uchar DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

void DelayMS(uint ms)
{
 	uchar t;
	while(ms--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Key_Event_Handle()
{
 	if(Key_State == 0)
	{
	 	Key_Flag_Idx=(Key_Flag_Idx+1)%3;
		switch(Key_Flag_Idx)
		{
		 	case 1:EA=1;ET0=1;TR0=1;break;
			case 2:EA=0;ET0=0;TR0=0;break;
			case 0:P0=0x3f;P2=0x3f;i=0;Second_Counts=0;
		}
	}
}

void main()
{
 	P0 = 0x3f;
	P2 = 0x3f;
	i = 0;
	Second_Counts = 0;
	Key_State = 1;
	TMOD = 0x01;
	TH0  = (65535-50000)/256;
	TL0  = (65535-50000)%256; 
	while(1)
	{
	 	if(Key_State != K1)
		{
		 	DelayMS(10);
			Key_State = K1;
			Key_Event_Handle();
		}
	}
}

void DSY_Refresh() interrupt 1
{
 	TH0  = (65535-50000)/256;
	TL0  = (65535-50000)%256;
	if(++i==2)
	{
	 	i = 0;
		++Second_Counts;
		P0 = DSY_CODE[Second_Counts/10];
		P2 = DSY_CODE[Second_Counts%10];
		if(Second_Counts == 100) Second_Counts = 0;
	}
}