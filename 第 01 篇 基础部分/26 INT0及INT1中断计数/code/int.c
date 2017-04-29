#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit k3 = P3^4;
sbit k4 = P3^5;

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff
};

uchar code Scan_BITs[]=
{
  	0x20,0x10,0x08,0x04,0x02,0x01
};

uchar data Buffer_Counts[]={0,0,0,0,0,0};
uint Count_A=0;
uint Count_B=0;

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Show_Counts()
{
 	uint i;
	Buffer_Counts[2] = Count_A / 100;
	Buffer_Counts[1] = Count_A % 100 /10;
	Buffer_Counts[0] = Count_A % 10;	
	if(Buffer_Counts[2]==0)
	{
	 	Buffer_Counts[2] = 0x0a;
		if(Buffer_Counts[1]==0)
		{
		 	Buffer_Counts[1]=0x0a;
		}
	}

	Buffer_Counts[5] = Count_B / 100;
	Buffer_Counts[4] = Count_B % 100 /10;
	Buffer_Counts[3] = Count_B % 10;	
	if(Buffer_Counts[5]==0)
	{
	 	Buffer_Counts[5] = 0x0a;
		if(Buffer_Counts[4]==0)
		{
		 	Buffer_Counts[4]=0x0a;
		}
	}
	for(i=0;i<6;i++)
	{
	 	P2 = Scan_BITs[i];
		P1 = DSY_CODE[Buffer_Counts[i]];
		DelayMS(1);
	}
}

void main()
{
 	IT0 = 1;
	IT1 = 1;
	PX0 = 1;
	IE  = 0x85;
	while(1)
	{
	 	if(k3 == 0) Count_A = 0;
		if(k4 == 0) Count_B = 0;
		Show_Counts();
	}
}

void EX_INT0() interrupt 0
{
 	Count_A++;
}

void EX_INT1() interrupt 2
{
 	Count_B++;
}