/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define Delay4us() {_nop_();_nop_();_nop_();_nop_();}

sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;
sbit SCL    = P1^0;
sbit SDA    = P1^1;

uchar Recv_Buffer[4];
uint Voltage[]={'0','0','0','0'};
bit bdata IIC_ERROR;
uchar LCD_Line_1[] = {"1- . V 2- . V"};
uchar LCD_Line_2[] = {"3- . V 4- . V"};

void Delay(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

bit LCD_Busy_Check()
{
 	bit Result;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EN = 1;
	Delay4us();
	Result = (bit)(P0&0x80);
	LCD_EN = 0;
	return Result;
}

void LCD_Write_Command(uchar cmd)
{
 	while(LCD_Busy_Check());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	_nop_();
	_nop_();
	P0 = cmd;
	Delay4us();
	LCD_EN = 1;
	Delay4us();
	LCD_EN = 0;
}

void LCD_Write_Data(uchar dat)
{
	while(LCD_Busy_Check());
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EN = 0;
	P0 = dat;
	Delay4us();
	LCD_EN = 1;
	Delay4us();
	LCD_EN = 0; 	
}

void LCD_Initialise()
{
 	LCD_Write_Command(0x38);Delay(5);
	LCD_Write_Command(0x0c);Delay(5);
	LCD_Write_Command(0x06);Delay(5);
	LCD_Write_Command(0x01);Delay(5);	
}

void LCD_Set_Position(uchar pos)
{
	LCD_Write_Command(pos | 0x80);	 	
}

void LCD_Display_A_Line(uchar Line_Addr,uchar s[])
{
 	uchar i;
	LCD_Set_Position(Line_Addr);
	for(i=0;i<16;i++)
	{
	 	LCD_Write_Data(s[i]);
	}
}

void Convert_To_Voltage(uchar val)
{
 	uchar Tmp;
	Voltage[2] = val/51+'0';
	Tmp = val%51*10;
	Voltage[1] = Tmp/51+'0';
	Tmp = Tmp%51*10;
	Voltage[0] = Tmp/51+'0';
}

void IIC_Start()
{
 	SDA = 1;
	SCL = 1;
	Delay4us();
	SDA = 0;
	Delay4us();
	SCL = 0;
}

void IIC_Stop()
{
 	SDA = 0;
	SCL = 1;
	Delay4us();
	SDA = 1;
	Delay4us();
	SCL = 0;
}

void Slave_ACK()
{
 	SDA = 0;
	SCL = 1;
	Delay4us();
	SCL = 0;
	SDA = 1;
}

void Slave_NOACK()
{
 	SDA = 1;
	SCL = 1;
	Delay4us();
	SCL = 0;
	SDA = 0;
}

void IIC_SendByte(uchar wd)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	SDA=(bit)(wd&0x80);
		_nop_();
		_nop_();
		SCL = 1;
		Delay4us();
	}
	Delay4us();
	SDA = 1;
	SCL = 1;
	Delay4us();

	IIC_ERROR = SDA;
	SCL = 0;
	Delay4us();
}

uchar IIC_ReceiveByte()
{
 	uchar i,rd = 0x00;
	for(i=0;i<8;i++)
	{
	 	SCL = 1;
		rd <<= 1;
		rd |= SDA;
		Delay4us();
		SCL = 0;
		Delay4us();
	}
	SCL = 0;
	Delay4us();
	return rd;
}

void ADC_PCF8591(uchar CtrlByte)
{
	uchar i;
	IIC_Start();
	IIC_SendByte(0x90);
	if(IIC_ERROR == 1) return;
	
	IIC_SendByte(CtrlByte);
	if(IIC_ERROR == 1) return;

  	IIC_Start();
	IIC_SendByte(0x91);
	if(IIC_ERROR == 1) return;
	IIC_ReceiveByte();
	Slave_ACK();
	for(i=0;i<4;i++)
	{
	 	Recv_Buffer[i++] = IIC_ReceiveByte();
		Slave_ACK();
	}
	Slave_NOACK();
	IIC_Stop();
}

void DAC_PCF8591(uchar CtrlByte,uchar dat)
{
	IIC_Start();
	Delay4us();
	IIC_SendByte(0x90);
	if(IIC_ERROR == 1) return;
	IIC_SendByte(CtrlByte);
	if(IIC_ERROR == 1) return;
	IIC_SendByte(dat);
	if(IIC_ERROR == 1) return;
	IIC_Stop();
	Delay4us();
	Delay4us();
}

void main()
{
 	LCD_Initialise();
	while(1)
	{
	 	ADC_PCF8591(0x40);
		Convert_To_Voltage(Recv_Buffer[0]);
		LCD_Line_1[2]=Voltage[2];
		LCD_Line_1[4]=Voltage[1];
		LCD_Line_1[5]=Voltage[0];
		Convert_To_Voltage(Recv_Buffer[1]);
		LCD_Line_1[11]=Voltage[2];
		LCD_Line_1[13]=Voltage[1];
		LCD_Line_1[14]=Voltage[0];
		Convert_To_Voltage(Recv_Buffer[2]);
		LCD_Line_2[2]=Voltage[2];
		LCD_Line_2[4]=Voltage[1];
		LCD_Line_2[5]=Voltage[0];
		Convert_To_Voltage(Recv_Buffer[3]);
		LCD_Line_2[11]=Voltage[2];
		LCD_Line_2[13]=Voltage[1];
		LCD_Line_2[14]=Voltage[0];
		
		LCD_Display_A_Line(0x00,   LCD_Line_1);	
		LCD_Display_A_Line(0x40,   LCD_Line_2);	

		DAC_PCF8591(0x40,Recv_Buffer[0]);
	}	
}








