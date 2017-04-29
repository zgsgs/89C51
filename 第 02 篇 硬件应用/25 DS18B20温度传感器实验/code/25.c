/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define delayNOP() {_nop_();_nop_();_nop_();_nop_();}

sbit DQ = P3^3;
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;

uchar code Temp_Disp_Title[]={"Current Temp : "};
uchar Current_Temp_Display_Buffer[]={" TEMP:   "};

uchar code Temperature_Char[8] = 
{
 	0x0c,0x12,0x12,0x0c,0x00,0x00,0x00,0x00
};

uchar code df_Table[]=
{
 	0,1,1,2,3,3,4,4,5,6,6,7,8,8,9,9
};

uchar CurrentT = 0;
uchar Temp_Value[]={0x00,0x00};
uchar Display_Digit[]={0,0,0,0};
bit DS18B20_IS_OK = 1;

void DelayXus(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<200;i++);
	}
}

bit LCD_Busy_Check()
{
 	bit result;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EN = 1;
	delayNOP();
	result = (bit)(P0&0x80);
	LCD_EN=0;
	return result;
}

void Write_LCD_Command(uchar cmd)
{
	while(LCD_Busy_Check());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	_nop_();
	_nop_();
	P0 = cmd;
	delayNOP();
	LCD_EN = 1;
	delayNOP();
	LCD_EN = 0;
}

void Write_LCD_Data(uchar dat)
{
	while(LCD_Busy_Check());
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EN = 0;
	P0 = dat;
	delayNOP();
	LCD_EN = 1;
	delayNOP();
	LCD_EN = 0;
}

void LCD_Initialise()
{
 	Write_LCD_Command(0x01);
	DelayXus(5);
	Write_LCD_Command(0x38);
	DelayXus(5);
	Write_LCD_Command(0x0c);
	DelayXus(5);
	Write_LCD_Command(0x06);
	DelayXus(5);	
}

void Set_LCD_POS(uchar pos)
{
 	Write_LCD_Command(pos|0x80);	
}

void Delay(uint x)
{
 	while(--x);
}

uchar Init_DS18B20()
{
 	uchar status;
	DQ = 1;
	Delay(8);
	DQ = 0;
	Delay(90);
	DQ = 1;
	Delay(8);
	DQ = 1;
	return status;
}

uchar ReadOneByte()
{
 	uchar i,dat=0;
	DQ = 1;
	_nop_();
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		dat >>= 1;
		DQ = 1;
		_nop_();
		_nop_();
		if(DQ)
			dat |= 0X80;
		Delay(30);
		DQ = 1;
	}
	return dat;
}

void WriteOneByte(uchar dat)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		DQ = dat& 0x01;
		Delay(5);
		DQ = 1;
		dat >>= 1;
	}
}

void Read_Temperature()
{
 	if(Init_DS18B20()==1)
		DS18B20_IS_OK=0;
	else
	{
		WriteOneByte(0xcc);
		WriteOneByte(0x44);
		Init_DS18B20();
		WriteOneByte(0xcc);
		WriteOneByte(0xbe);
		Temp_Value[0] = ReadOneByte(); 
		Temp_Value[1] = ReadOneByte();
		DS18B20_IS_OK=1;	
	}	
}

void Display_Temperature()
{
 	uchar i;
	uchar t = 150, ng = 0;
	if((Temp_Value[1]&0xf8)==0xf8)
	{
	 	Temp_Value[1] = ~Temp_Value[1];
		Temp_Value[0] = ~Temp_Value[0]+1;
		if(Temp_Value[0]==0x00)
			Temp_Value[1]++;
		ng = 1;	
	}
	Display_Digit[0] = df_Table[Temp_Value[0]&0x0f];
	CurrentT = ((Temp_Value[0]&0xf0)>>4) | ((Temp_Value[1]&0x07)<<4);
	Display_Digit[3] = CurrentT/100;
	Display_Digit[2] = CurrentT%100/10;
	Display_Digit[1] = CurrentT%10;
	Current_Temp_Display_Buffer[11] = Display_Digit[0] + '0';
	Current_Temp_Display_Buffer[10] = '.';
	Current_Temp_Display_Buffer[9]  = Display_Digit[1] + '0';
	Current_Temp_Display_Buffer[8]  = Display_Digit[2] + '0';
	Current_Temp_Display_Buffer[7]  = Display_Digit[3] + '0';
	if(Display_Digit[3] == 0)
		Current_Temp_Display_Buffer[7]  = ' ';
	if(Display_Digit[2] == 0&&Display_Digit[3]==0)
		Current_Temp_Display_Buffer[8]  = ' ';
	if(ng)
	{
	 	if(Current_Temp_Display_Buffer[8]  == ' ')
			Current_Temp_Display_Buffer[8]  = '-';
		else if(Current_Temp_Display_Buffer[7]  == ' ')
			Current_Temp_Display_Buffer[7]  = '-';
		else 
			Current_Temp_Display_Buffer[6]  = '-';
	}
	Set_LCD_POS(0x00);
	for(i=0;i<16;i++)
	{
		Write_LCD_Data(Temp_Disp_Title[i]); 	
	}
	Set_LCD_POS(0x40);
	for(i=0;i<16;i++)
	{
		Write_LCD_Data(Current_Temp_Display_Buffer[i]); 	
	}		
	Set_LCD_POS(0x4d);
	Write_LCD_Data(0x00);
	Set_LCD_POS(0x4e);
	Write_LCD_Data('C');
}

void main()
{
 	LCD_Initialise();
	Read_Temperature();
	Delay(50000);
	Delay(50000);
	while(1)
	{
	 	Read_Temperature();
		if(DS18B20_IS_OK) 
			Display_Temperature();
		DelayXus(100);		
	}

}




