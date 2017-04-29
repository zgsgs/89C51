#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x7f,0x6f,0x00
};
uchar Display_Buffer[3]={0,0,0};
uint Count = 0;
sbit Clear_Key = P3^6;

void Show_Count_ON_DSY()
{
 	Display_Buffer[2] = Count / 100;
	Display_Buffer[1] = Count % 100 /10;
	Display_Buffer[0] = Count % 10;	
	if(Display_Buffer[2]==0)
	{
	 	Display_Buffer[2] = 0x0a;
		if(Display_Buffer[1]==0)
		{
		 	Display_Buffer[1]=0x0a;
		}
	}
	P0 = DSY_CODE[Display_Buffer[0]];
	P1 = DSY_CODE[Display_Buffer[1]];
	P2 = DSY_CODE[Display_Buffer[2]];
}

void main()
{
 	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	IE = 0x81;
	IT0 = 1;
	while(1)
	{
	 	if(Clear_Key == 0)
			Count = 0;
		Show_Count_NO_DSY();
	}
}

void EX_INT0() interrupt 0
{
 	Count ++;
}