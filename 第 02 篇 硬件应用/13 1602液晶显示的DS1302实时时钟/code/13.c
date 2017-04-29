/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char

sbit IO = P1^0;
sbit SCLK = P1^1;
sbit RST = P1^2;
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;

uchar *WEEK[]=
{
 	"SUN","***","MON","TUS","WEN","THU","FRI","SAT"
};
uchar LCD_DSY_BUFFER1[]={"DATE 00-00-00    "};
uchar LCD_DSY_BUFFER2[]={"TIME 00:00:00    "};
uchar DateTime[7];

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void Write_A_Byte_TO_DS1302(uchar x)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	IO=x&0x01;SCLK=1;SCLK=0;x>>=1;
	}
}

uchar Get_A_Byte_FROM_DS1302()
{
 	uchar i,b=0x00;
	for(i=0;i<8;i++)
	{
	 	b |= _crol_((uchar)IO,i);
		SCLK=1;SCLK=0;
	}
	return b/16*10+b%16;
}

uchar Read_Data(uchar addr)
{
 	uchar dat;
	RST = 0;SCLK=0;RST=1;
   	Write_A_Byte_TO_DS1302(addr);
	dat = Get_A_Byte_FROM_DS1302();
   	SCLK=1;RST=0;
	return dat;
}

void GetTime()
{
 	uchar i,addr = 0x81;
	for(i=0;i<7;i++)
	{
	 	DateTime[i]=Read_Data(addr);addr+=2;
	}
}

uchar Read_LCD_State()
{
 	uchar state;
	RS=0;RW=1;EN=1;DelayMS(1);
	state=P0;
	EN = 0;DelayMS(1);
	return state;
}


void LCD_Busy_Wait()
{
 	while((Read_LCD_State()&0x80)==0x80);
	DelayMS(5);
}

void Write_LCD_Data(uchar dat)
{
 	LCD_Busy_Wait();
	RS=1;RW=0;EN=0;P0=dat;EN=1;DelayMS(1);EN=0;	
}

void Write_LCD_Command(uchar cmd)
{
 	LCD_Busy_Wait();
	RS=0;RW=0;EN=0;P0=cmd;EN=1;DelayMS(1);EN=0;	
}

void Init_LCD()
{
 	Write_LCD_Command(0x38);
	DelayMS(1);	
	Write_LCD_Command(0x01);
	DelayMS(1);	
	Write_LCD_Command(0x06);
	DelayMS(1);	
	Write_LCD_Command(0x0c);
	DelayMS(1);	
}

void Set_LCD_POS(uchar p)
{
 	Write_LCD_Command(p|0x80);	
}

void Display_LCD_String(uchar p,uchar *s)
{
 	uchar i;
	Set_LCD_POS(p);
	for(i=0;i<16;i++)
	{
		Write_LCD_Data(s[i]);
		DelayMS(1); 	
	}
}

void Format_DateTime(uchar d,uchar *a)
{
 	a[0]=d/10+'0';
	a[1]=d%10+'0';
}

void main()
{
 	Init_LCD();
	while(1)
	{
	 	GetTime();
		Format_DateTime(DateTime[6],LCD_DSY_BUFFER1+5);
		Format_DateTime(DateTime[4],LCD_DSY_BUFFER1+8);
		Format_DateTime(DateTime[3],LCD_DSY_BUFFER1+11);

		strcpy(LCD_DSY_BUFFER1+13,WEEK[DateTime[5]]);

		Format_DateTime(DateTime[2],LCD_DSY_BUFFER1+5);
		Format_DateTime(DateTime[1],LCD_DSY_BUFFER1+8);
		Format_DateTime(DateTime[0],LCD_DSY_BUFFER1+11);

		Display_LCD_String(0x00,LCD_DSY_BUFFER1);
		Display_LCD_String(0x40,LCD_DSY_BUFFER2);
	}
}