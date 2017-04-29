#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define NOP4() {_nop_();_nop_();_nop_();_nop_();}

sbit SCL = P1^0;
sbit SDA = P1^1;

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90	
};

uchar DISP_Buffer[]={0,0,0};
uchar Count = 0;

void DelayMS(uint x)
{
	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Start()
{
 	SDA=1;SCL=1;NOP4();SDA=0;NOP4();SCL=0;
}

void Stop()
{
 	SDA=0;SCL=0;NOP4();SCL=1;NOP4();SDA=1;
}

void RACK()
{
 	SDA=1;NOP4();SCL=1;NOP4();SCL=0;
}

void NO_ACK()
{
 	SDA=1;SCL=1;NOP4();SCL=0;SDA=0;
}

void Write_A_Byte(uchar b)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	b<<=1;SDA=CY;_nop_();SCL=1;NOP4();SCL=0;
	}
	RACK();
}

uchar Receive_A_Byte()
{
 	uchar i,d;
	for(i=0;i<8;i++)
	{
	 	SCL=1;d<<=1;d|=SDA;SCL=0;
	}
	return d;
}

void Write_Random_Address_Byte(uchar add,uchar dat)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(add);
	Write_A_Byte(dat);
	Stop();
	DelayMS(10);
}

uchar Read_Current_Address_Data()
{
 	uchar d;
	Start();
	Write_A_Byte(0xa1);
	d=Receive_A_Byte();
	NO_ACK();
	Stop();
	return d;
}

uchar Random_Read(uchar addr)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(addr);
	Stop();
	return Read_Current_Address_Data();		
}

void Convert_And_Display()
{
 	DISP_Buffer[2] = Count/10;
	DISP_Buffer[1] = Count%100/10;
	DISP_Buffer[0] = Count%100%10;
	if(DISP_Buffer[2] == 0)
	{
	 	DISP_Buffer[2] = 10;
		if(DISP_Buffer[1] == 0)
		{
		 	DISP_Buffer[1] = 10;	
		}
	}
	P2 = 0x80;
	P0 = DSY_CODE[DISP_Buffer[0]];
	DelayMS(2);
	P2 = 0x40;
	P0 = DSY_CODE[DISP_Buffer[1]];
	DelayMS(2);
	P2 = 0x20;
	P0 = DSY_CODE[DISP_Buffer[2]];
	DelayMS(2); 
}

void main()
{
 	Count = Random_Read(0x00) + 1;
	Write_Random_Address_Byte(0x00,Count);
	while(1)
		Convert_And_Display();	
}