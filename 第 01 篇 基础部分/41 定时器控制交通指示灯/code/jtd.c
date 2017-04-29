/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit RED_A = P0^0;
sbit YELLOW_A = P0^1;
sbit GREEN_A = P0^2;
sbit RED_B = P0^3;
sbit YELLOW_B = P0^4;
sbit GREEN_B = P0^5;

uchar Time_Count = 0,Flash_Count = 0,Operation_Type = 1;

void T0_INT() interrupt 1
{
 	TH0 = -50000/256;
	TL0 = -50000%256;
	switch(Operation_Type)
	{
	 	case 1:
			RED_A=0;YELLOW_A=0;GREEN_A=1;
			RED_B=1;YELLOW_B=0;GREEN_B=0;
			if(++Time_Count != 100) return;
			Time_Count=0;
			Operation_Type = 2;
			break;
		case 2:
			if(++Time_Count != 8) return;
			Time_Count=0;
			YELLOW_A=!YELLOW_A;
			GREEN_A=0;
			if(++Flash_Count != 10) return;
			Flash_Count=0;
			Operation_Type = 3;
			break;
		case 3:
			RED_A=1;YELLOW_A=0;GREEN_A=0;
			RED_B=0;YELLOW_B=0;GREEN_B=1;
			if(++Time_Count != 100) return;
			Time_Count=0;
			Operation_Type = 4;
			break;	
		case 4:
			if(++Time_Count != 8) return;
			Time_Count=0;
			YELLOW_B=!YELLOW_B;
			GREEN_B=0;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 1;
			break;	
	}
}

void main()
{
 	TMOD = 0x01;
	IE = 0x82;
	TR0 = 1;
	while(1);
}