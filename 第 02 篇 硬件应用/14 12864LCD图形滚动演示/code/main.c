#include "LCD_12864.h"
#include <stdio.h>
extern void cls();
extern uchar LCD_Initialise();
extern uchar LCD_Write_Command(uchar cmd);
extern uchar LCD_Write_Command_P2(uchar cmd,uchar para1,uchar para2);
extern uchar LCD_Write_Data(uchar dat);
extern void Set_LCD_POS(uchar row,uchar col);
extern uchar code LCD_WIDTH;
extern uchar code LCD_HEIGHT;
sbit S1 = P1^0;
sbit S2 = P1^1;

uchar code ImageX[] = 
{
 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};

void main()
{
 	uchar i,j,m;
	uint k,x;
	LCD_Initialise();
	Set_LCD_POS(0,0);
	cls();
	while(1)
	{
	 	if(S1!=0)
		{
		 	LCD_Write_Command_P2(LC_GRH_STP,0,0);
			for(i=0;i<LCD_HEIGHT;i++)
			{
			 	Set_LCD_POS(i,0);
				LCD_Write_Command(LC_AUT_WR);
				for(j=0;j<LCD_WIDTH;j++)
				{
				 	m = ImageX[i*LCD_WIDTH + j];
					if(S2 == 0) 
						m = ~m;
					LCD_Write_Data(m);
				}
				LCD_Write_Command(LC_AUT_OVR);
			}
		}
		else
		{
		 	k = 0;
			while(k!=128/8*LCD_HEIGHT)
			{
				LCD_Write_Command_P2(LC_GRH_STP,k%256,k/256);
				for(x=0;x<5000;x++);
				k+=LCD_WIDTH; 	
			}
		}
	}
	for(x=0;x<40000;x++);
} 