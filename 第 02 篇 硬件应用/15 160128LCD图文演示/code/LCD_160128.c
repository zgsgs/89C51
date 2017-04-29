#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#include <LCD_160128.h>

sbit RESET = P3^3;

#define ASC_CHR_WIDTH   8
#define ASC_CHR_HEIGHT 12
#define HZ_CHR_HEIGHT  12
#define HZ_CHR_WIDTH   12
uchar code LCD_WIDTH = 20;
uchar code LCD_HEIGHT= 128;
uchar code ASC_MSK[96*12]=
{
 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

uchar gCurRow,gCurCol;
uchar tCurRow,tCurCol;
uchar ShowModeSW;
uint txthome,grhome;

uchar Status_BIT_01();
uchar Status_BIT_3();
uchar GetCol();
uchar GetRow();
uchar LCD_Write_Command(uchar cmd);
uchar LCD_Write_Command_P1(uchar cmd,uchar para1);
uchar LCD_Write_Command_P2(uchar cmd,uchar para1,uchar para2);
uchar LCD_Write_Data(uchar dat);
uchar LCD_Read_Data();
void cls();
uchar LCD_Initialise();
void Set_LCD_POS(uchar row,uchar col);
void charout(uchar *str);
uchar dprintf(uchar x,uchar y,uchar *fmt);
void OutToLCD(uchar Dat,uchar x,uchar y);

void Line(uchar x1,uchar y1,uchar x2,uchar y2,bit Mode);
void Pixel(uchar x,uchar y,bit Mode);

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

uchar LCD_Read_Data()
{
 	if(Status_BIT_01()==0) return 1;
	return LCMDW;
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

uchar Display_Str_at_xy(uchar x,uchar y,uchar *fmt)
{
 	char c1,c2,cData;
	uchar i=0,j,uLen;
	uLen = strlen(fmt);
	while(i<uLen)
	{
	 	c1 = fmt[i];
		c2 = fmt[i+1];
		Set_LCD_POS(y,x/8);
		if(c1>=0)
		{
		 	if(c1<0x20)
			{
			 	switch(c1)
				{
				 	case CR:
					case LF:
							i++;
							x=0;
							if(y<112) y+=HZ_CHR_HEIGHT;
							continue;
					case BS:
							i++;
							if(y>ASC_CHR_WIDTH) y-=ASC_CHR_WIDTH;
							cData=0x00;
							break;	
				}
			}
			for(j=0;j<ASC_CHR_HEIGHT;j++)
			{
			 	if(c1>=0x1f)
				{
				 	cData = ASC_MSK[(c1-0x1f)*ASC_CHR_HEIGHT+j];
					Set_LCD_POS(y+j,x/8);
					if((x%8)==0)
					{
					 	LCD_Write_Command(LC_AUT_WR);
						LCD_Write_Data(cData);
						LCD_Write_Command(LC_AUT_OVR);
					}
					else
						OutToLCD(cData,x,y+j);
				}
				Set_LCD_POS(y+j,x/8);
			}
			if(c1!=BS) x+=ASC_CHR_WIDTH;
		}
		i++;
	}
	return uLen;
}

void OutToLCD(uchar Dat,uchar x,uchar y)
{
 	uchar dat1,dat2,a,b;
	b = x%8;
	a = 8-b;
	Set_LCD_POS(y,x/8);
	LCD_Write_Command(LC_AUT_RD);
	dat1 = LCD_Read_Data();
	dat2 = LCD_Read_Data();
	dat1 = (dat1 &(0xff<<a)) | (Dat>>b);
	dat2 = (dat1 &(0xff>>b)) | (Dat<<a);
	LCD_Write_Command(LC_AUT_OVR);
   	Set_LCD_POS(y,x/8);
	LCD_Write_Command(LC_AUT_WR);
	LCD_Write_Data(dat1);
	LCD_Write_Data(dat2);
	LCD_Write_Command(LC_AUT_OVR);
}

void Pixel(uchar x,uchar y,bit Mode)
{
 	uchar start_addr,dat;
	start_addr=7-(x%8);
	dat = LC_BIT_OP | start_addr;
	if(Mode) dat |= 0x08;
	Set_LCD_POS(y,x/8);
	LCD_Write_Command(LC_BIT_OP | dat);
}

void Exchange(uchar *a,uchar *b)
{
 	uchar t;
	t = *a;*a = *b;*b = t;
}

void Line(uchar x1,uchar y1,uchar x2,uchar y2,bit Mode)
{
 	uchar x,y;
	float k,b;
	if(abs(y1-y2)<=abs(x1-x2))
	{
	 	k=(float)(y1-y2)/(float)(x2-x1);
		b=y1-k*x1;
		if(x1>x2) Exchange(&x1,&x2);

		for(x=x1;x<=x2;x++)
		{
		 	y=(uchar)(k*x+b);
			Pixel(x,y,Mode);
		}
	}
	else 
	{
	 	k=(float)(x2-x1)/(float)(y2-y1);
		b=x1-k*y1;
		if(y1>y2) Exchange(&y1,&y2);

		for(y=y1;y<=y2;y++)
		{
		 	x=(uchar)(k*y+b);
			Pixel(x,y,Mode);
		}	
	}
}



