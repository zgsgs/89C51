#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char 
#define uint unsigned int

uchar code M[3][8]=
{
 	{0x00,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x00},
	{0x00,0x38,0x44,0x54,0x44,0x38,0x00,0x00},
	{0x00,0x20,0x30,0x38,0x3c,0x3e,0x00,0x00}
};

uchar i,j;
void main()
{
 	P0 = 0xff;
	P1 = 0xff;
	TMOD = 0x01;
	TH0  = (65535-2000)/256;
	TL0  = (65535-2000)%256;
	IT0 = 1;
	IE  = 0x83;
	i   = 0xff;
	while(1);
}

void Key_Down() interrupt 0
{
 	P0 = 0xff;
	P1 = 0x80;
	j = 0;
	i = (i+1)%3;
	TR0 = 1;
}

void Show_Dot_Matrix() interrupt 1
{
	TH0  = (65535-2000)/256;
	TL0  = (65535-2000)%256;
	P1 = _crol_(P1,1);
	P0 = ~M[i][j];
	j=(j+1)%8;	
}