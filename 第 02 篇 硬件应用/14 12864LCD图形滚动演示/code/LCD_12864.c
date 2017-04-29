#include <stdio.h>
#include <math.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#include "LCD_12864.h"

sbit RESET = P3^3;
uchar code LCD_WIDTH = 16;
uchar code LCD_HEIGHT = 64;
uchar gCurRow,gCurCol;
uchar tCurRow,tCurCol;
uchar ShowModeSW;
uint txthome,grhome;

uchar Status_BIT_01();
uchar Status_BIT_3();
uchar LCD_Write_Command(uchar cmd);
uchar LCD_Write_Command_P1(uchar cmd,uchar para1);
uchar LCD_Write_Command_P2(uchar cmd,uchar para1,uchar para2);
uchar LCD_Write_Data(uchar dat);
void cls();
uchar LCD_Initialise();
void Set_LCD_POS(uchar row,uchar col);
uchar Status_BIT_01()
{
 	uchar i;
	for(i=5;i>0;i--)
	{
	 	if((LCMCW & 0x03)==0x03)
		break;
	}
	return i;
}

uchar Status_BIT_3()
{
 	uchar i;
	for(i=5;i>0;i--)
	{
	 	if((LCMCW & 0x08)==0x08)
		break;
	}
	return i;	
}

uchar LCD_Write_Command_P2(uchar cmd,uchar para1,uchar para2)
{
 	if(Status_BIT_01()==0) return 1;
	LCMDW = para1;
   	if(Status_BIT_01()==0) return 2;
	LCMDW = para2;
	if(Status_BIT_01()==0) return 3;
	LCMDW = cmd;
	return 0;
}

uchar LCD_Write_Command_P1(uchar cmd,uchar para1)
{
 	if(Status_BIT_01()==0) return 1;
	LCMDW = para1;
   	if(Status_BIT_01()==0) return 2;
	LCMDW = cmd;
	return 0;	
}  

uchar LCD_Write_Command(uchar cmd)
{
	if(Status_BIT_01()==0) return 1;
	LCMDW = cmd;
	return 0; 	
}

uchar LCD_Write_Data(uchar dat)
{
 	if(Status_BIT_3()==0) return 1;
	LCMDW = dat;
	return 0; 		
}

void Set_LCD_POS(uchar row,uchar col)
{
 	uint Pos;
	Pos = row*LCD_WIDTH+col;
	LCD_Write_Command_P2(LC_ADD_POS,Pos%256,Pos/256);
	gCurRow = row;
	gCurCol = col;
}

void cls()
{
 	uint i;
   	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);
	LCD_Write_Command(LC_AUT_WR);
	for(i=0;i<0x2000;i++)
	{
	 	Status_BIT_3();
		LCD_Write_Data(0x00);
	}
	LCD_Write_Command(LC_AUT_OVR);
	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);
	gCurRow = 0;
	gCurCol = 0;
}

uchar LCD_Initialise()
{
 	RESET = 0;
	RESET = 1;
	LCD_Write_Command_P2(LC_TXT_STP,0x00,0x00);
	LCD_Write_Command_P2(LC_TXT_WID,LCD_WIDTH,0x00);
	LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);
	LCD_Write_Command_P2(LC_GRH_WID,LCD_WIDTH,0x00);
	LCD_Write_Command_P1(LC_CGR_POS,CGRAMSTART >> 11);
   	LCD_Write_Command(LC_CUR_SHP | 0x01);
	LCD_Write_Command(LC_MOD_OR);
	LCD_Write_Command(LC_DIS_SW | 0x08);
	grhome = GRSTART;
	txthome = TXTSTART;
	return 0;
}





