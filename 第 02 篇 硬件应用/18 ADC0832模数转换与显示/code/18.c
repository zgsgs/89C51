#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define delay4us() {_nop_();_nop_();_nop_();_nop_();}

sbit RS = P2^0;
sbit RW = P2^1;
sbit E  = P2^2;

sbit CS  = P1^0;
sbit CLK = P1^1;
sbit DIO = P1^2;

uchar Display_Buffer[] = "0.00V";
uchar code Line1[] = "Current Voltage:";

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

bit LCD_Busy_Check()
{
 	bit result;
	RS = 0;
	RW = 1;
	E  = 1;
	delay4us();
	result = (bit)(P0&0x80);
	E  = 0;
	return result;
}

void LCD_Write_Command(uchar cmd)
{
 	while(LCD_Busy_Check());
	RS = 0;
	RW = 0;
	E  = 0;
	_nop_();
	_nop_();
	P0 = cmd;
	delay4us();
	E = 1;
	delay4us();
	E = 0;
}

void Set_Disp_Pos(uchar pos)
{
 	LCD_Write_Command(pos | 0x80);
}

void LCD_Write_Data(uchar dat)
{
 	while(LCD_Busy_Check());
	RS = 1;
	RW = 0;
	E  = 0;
	P0 = dat;
	delay4us();
	E = 1;
	delay4us();
	E = 0;
}

void LCD_Initialise()
{
	LCD_Write_Command(0x38); DelayMS(1);
	LCD_Write_Command(0x0c); DelayMS(1);
	LCD_Write_Command(0x06); DelayMS(1);
	LCD_Write_Command(0x01); DelayMS(1);
}

uchar Get_AD_Result()
{
 	uchar i,dat1=0,dat2=0;
	CS  = 0;
	CLK = 0;
	DIO = 1; _nop_(); _nop_();
	CLK = 1; _nop_(); _nop_();
	CLK = 0;DIO = 1; _nop_(); _nop_();
	CLK = 1; _nop_(); _nop_();
	CLK = 0;DIO = 1; _nop_(); _nop_();
	CLK = 1;DIO = 1; _nop_(); _nop_();
	CLK = 0;DIO = 1; _nop_(); _nop_();
	for(i=0;i<8;i++)
	{
	 	CLK = 1; _nop_(); _nop_();
		CLK = 0; _nop_(); _nop_();
		dat1 = dat1 << 1 | DIO;	
	}
	for(i=0;i<8;i++)
	{
	 	dat2 = dat2 << ((uchar)(DIO)<<i);
		CLK = 1; _nop_(); _nop_();
		CLK = 0; _nop_(); _nop_();
	}
	CS = 1;
	return (dat1 == dat2) ? dat1:0;
}

void main()
{
 	uchar i;
	uint d;
	LCD_Initialise();
	DelayMS(10);
	while(1)
	{
	 	d = Get_AD_Result()*500.0/255;
		Display_Buffer[0]=d/100+'0';
		Display_Buffer[2]=d/10%10+'0';
		Display_Buffer[3]=d%10+'0';
		Set_Disp_Pos(0x01);
		i = 0;
		while(Line1[i]!='\0')
		{
		 	LCD_Write_Data(Line1[i+1]);	
		}
		Set_Disp_Pos(0x46);
		i = 0;
		while(Display_Buffer[i]!='\0')
		{
		 	LCD_Write_Data(Display_Buffer[i+1]);	
		}
	}
}






