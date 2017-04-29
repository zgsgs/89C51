#include <LCD_160128.h>
#include <stdio.h>
extern void cls();
extern uchar LCD_Initialise();
extern uchar LCD_Write_Command(uchar cmd);
extern uchar LCD_Write_Command_P2(uchar cmd,uchar para1,uchar para2);
extern uchar LCD_Write_Data(uchar dat);
extern void Set_LCD_POS(uchar row,uchar col);
extern void Line(uchar x1,uchar y1,uchar x2,uchar y2,bit Mode);
extern uchar Display_Str_at_xy(uchar x,uchar y,char *fmt);

extern uchar code LCD_WIDTH;
extern uchar code LCD_HEIGHT;
sbit S1 = P1^0;
sbit S2 = P1^1;
sbit S3 = P1^2;
sbit S4 = P1^3;

uchar code ImageX[]=
{
 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

uchar Current_Operation = 0;
uchar Statistics_Data[]={20,70,80,40,90,65,30}; 

void Draw_Bar_Graph(uchar d[])
{
 	uchar i,h;
	Line(4,2,4,100,1);
	Line(4,100,158,100,1);
	Line(4,2,1,10,1);
	Line(4,2,7,10,1);
	Line(158,100,152,97,1);
	Line(158,100,152,103,1);
	for(i=0;i<7;i++)
	{
	 	h=100-d[i];
		Line(10+i*20,h,10+i*20,100,1);
		Line(10+i*20,h,10+i*20+15,h,1);
		Line(10+i*20+15,h,10+i*20+15,100,1);
	}
}

void main()
{
 	uchar i,j,m,c=0;uint k,x;
	LCD_Initialise();
	Set_LCD_POS(0,0);
	cls();
	while(1)
	{
	 	if(S1==0) Current_Operation = 1;
		if(S2==0) Current_Operation = 2;
		if(S3==0) Current_Operation = 3;
		if(S4==0) Current_Operation = 4;
		if(c==Current_Operation) goto delayx;
		c=Current_Operation;
		switch(Current_Operation)
		{
		 	case 1:
			case 2:
					LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);
					for(i=0;i<LCD_HEIGHT;i++)
					{
					 	Set_LCD_POS(i,0);
						LCD_Write_Command(LC_AUT_WR);
						for(j=0;j<LCD_WIDTH;j++)
						{
						 	m=ImageX[i*LCD_WIDTH+j];
							if(S2==0) m=~m;
							LCD_Write_Data(m);
						}
						LCD_Write_Command(LC_AUT_OVR);
					}
					break;
			case 3:
					k=0;
					while(k!=LCD_WIDTH*LCD_HEIGHT)
					{
					 	LCD_Write_Command_P2(LC_GRH_STP,k%256,k/256);
						for(x=0;x<5000;x++);
						k+=LCD_WIDTH;
					}
					break;
			case 4:
					LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);
					Set_LCD_POS(0,0);
					cls();
					Draw_Bar_Graph(Statistics_Data);
					Display_Str_at_xy(12,110,"statistics Graph");
					break;	
		}
		delayx : for(x=0;x<20000;x++);	
	}
}



