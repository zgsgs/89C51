#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf
};
uchar code Table_OF_Digits[][8]=
{
 	{0,9,10,1,2,10,2,5},
	{2,1,10,5,7,10,3,9},
};

uchar i = 0,j=0;
uint t = 0;

void main()
{
 	P3 = 0x80;
	TMOD = 0x00;
	TH0 = (8191-4000)/32;
	TL0 = (8191-4000)%32;
	IE = 0x82;
	TR0 = 1;
	while(1);
}

void DSY_Show() interrupt 1
{
 	TH0 = (8191-4000)/32;
	TL0 = (8191-4000)%32;
	P3 = _crol_(P3,1);
	P0 = DSY_CODE[Table_OF_Digits[i][j]];
	j = (j+1)%8;
	if(++t!=350) return;
	t = 0;
	i = (i+1)%2;	
}