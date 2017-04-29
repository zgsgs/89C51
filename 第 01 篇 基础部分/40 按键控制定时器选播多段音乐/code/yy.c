#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar Song_Index = 0,Tone_Index = 0;
sbit SPK = P3^7;
sbit K1 = P1^0;
uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90
};

uchar code HI_LIST[]=
{
 	0,266,229,232,233,236,238,240,241,242,244,245,246,247,248
};
uchar code LO_LIST[]=
{
 	0,4,13,10,20,3,8,6,2,23,5,26,1,4,3
};

uchar code Song[][50]=
{
 	{1,2,3,1,1,2,3,1,3,4,5,3,4,5,3,4,5,5,6,1,2,3,6,2,6,6,2,3,4,5,2,5,2,3,-1},
	{3,3,3,5,6,2,3,4,6,2,6,4,2,1,2,3,6,2,5,6,3,4,5,6,2,3,1,2,3,5,1,2,3,-1},
	{3,2,1,3,2,1,1,2,3,1,3,5,1,5,4,6,2,6,3,4,2,3,6,2,3,4,2,1,1,1,2,2,2,3,3,2,6,3,5,3,5,1,2,6,4,5,-1}
};

uchar code Len[][50]=
{
 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,-1},
	{1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,-1},
	{1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,1,1,1,1,2,2,-1}
};

void EX0_INT() interrupt 0
{
 	TR0 = 0;
	Song_Index = (Song_Index+1)%3;
	Tone_Index = 0;
	P2 = DSY_CODE[Song_Index];
}

void T0_INT() interrupt 1
{
 	SPK = !SPK;
	TH0 = HI_LIST[Song[Song_Index][Tone_Index]];
	TL0 = LO_LIST[Song[Song_Index][Tone_Index]];
}

void delay(uint ms)
{
 	uchar i;
	while(ms--)
	{
		for(i=0;i<120;i++);
	}
}

void main()
{
 	P2 = 0xc0;
	IE = 0x83;
	TMOD = 0x00;
	IT0 = 1;
	IP = 0x02;
	while(1)
	{
	 	while(K1==1);
		while(K1==0);
		TR0 = 1;
		Tone_Index = 0;
		while(Song[Song_Index][Tone_Index]!=-1&&K1==1&&TR0==1)
		{
		 	delay(300*Len[Song_Index][Tone_Index]);
			Tone_Index++;
		}
		TR0 = 0;
		while(K1==0);
	}
}