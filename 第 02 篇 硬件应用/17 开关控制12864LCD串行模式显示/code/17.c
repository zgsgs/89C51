#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define Max_Page 6
#define DelayNOP() {_nop_();_nop_();_nop_();_nop_();}

sbit CS  = P2^3;
sbit RES = P2^4;
sbit SDA = P2^5;
sbit SCLK = P2^6;
sbit A0  = P2^7;
sbit K1  = P1^5;
sbit K2  = P1^6;
sbit S1  = P1^7;

uchar Auto_Flash;
uchar Page_Idx;
uchar Disp_Flag;

uchar code Q[8]=
{
 	0x00,0x5e,0x21,0x51,0x41,0x41,0x3e,0x00
};

uchar code Clip_BMP[1024]=
{
	0xff,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
};

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void Write_Command(uchar c)
{
 	uchar i;
	SCLK = 0;
	CS = 0;
	A0 = 0;
	DelayNOP();
	for(i=0;i<8;i++)
	{
	 	c<<=1;
		SDA = CY;
		SCLK = 1;
		DelayNOP();
		SCLK = 0;
	}
	DelayNOP();
	CS = 1;
}

void Write_Data(uchar d)
{
 	uchar i;
	SCLK = 0;
	CS = 0;
	A0 = 1;
	DelayNOP();
	for(i=0;i<8;i++)
	{
	 	d<<=1;
		SDA = CY;
		SCLK = 1;
		DelayNOP();
		SCLK = 0;
	}
	DelayNOP();
	CS = 1;
}

void Init_LCD()
{
 	RES = 0;
	DelayMS(10);
	RES = 1;
	Write_Command(0xa2);
	Write_Command(0xa0);
	Write_Command(0xc8);
	Write_Command(0x27);
	Write_Command(0x81);
	Write_Command(0x1b);
	Write_Command(0x2c);
	Write_Command(0x2e);
	Write_Command(0x2f);
	Write_Command(0xa4);
	Write_Command(0xaf);
}

void Disp_All()
{
 	uchar i,j;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<128;j++)
		{
		 	Write_Data(0xff);
		}
	}
}

void Disp_Off()
{
 	uchar i,j;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<128;j++)
		{
		 	Write_Data(0x00);
		}
	}
}

void Disp_Frame()
{
 	uchar i,j;
	Write_Command(0x40);
	Write_Command(0xb0);
	Write_Command(0x10);
	Write_Command(0x00);
	Write_Data(0xff);
	for(j=0;j<126;j++)
	{
	 	Write_Data(0x01);
	}
	Write_Data(0xff);
	for(i=0;i<6;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		Write_Data(0xff);
		for(j=0;j<126;j++)
		{
	 		Write_Data(0x00);
		}
		Write_Data(0xff);	
	}
	Write_Command(0xb7);
	Write_Command(0x10);
	Write_Command(0x00);
	Write_Data(0xff);
	for(j=0;j<126;j++)
	{
	 	Write_Data(0x80);
	}
	Write_Data(0xff);
}

void Disp_Checker0()
{
 	uchar i,j;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<64;j++)
		{
		 	Write_Data(0xaa);
			Write_Data(0x55);
		}
	}
}

void Disp_Checker1()
{
 	uchar i,j;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<64;j++)
		{
		 	Write_Data(0x55);
			Write_Data(0xaa);
		}
	}
}

void Disp_Q()
{
 	uchar i,j,k;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<16;j++)
		{
		 	for(k=0;k<8;k++)
			Write_Data(Q[k]);
		}
	}
}

void Disp_Clip()
{
 	uchar i,j;
	Write_Command(0x40);
	for(i=0;i<8;i++)
	{
	 	Write_Command(0xb0+i);
		Write_Command(0x10);
		Write_Command(0x00);
		for(j=0;j<128;j++)
		{
		 	Write_Data(Clip_BMP[i*128+j]);
		}
	}	
}

void Do_Key()
{
 	P1 = 0xff;
	DelayMS(5);
	if(S1 == 0) Auto_Flash = 1;
	else Auto_Flash = 0;
	if(K1 == 0)
	{
	 	Disp_Flag = 1;
		Page_Idx++;
		if(Page_Idx >= Max_Page)
			Page_Idx = 0;
	}
	if(K2 == 0)
	{
	 	Disp_Flag = 1;
		if(Page_Idx > 0)
		{
			Page_Idx--;
		}
		else Page_Idx = Max_Page - 1;
	}
	DelayMS(100);
}

void main()
{
	Auto_Flash = 1;
	Page_Idx = 0;
	Disp_Flag = 1;
	Init_LCD();
	DelayMS(5);
	Disp_Off();
	DelayMS(200);
	while(1)
	{
	 	Do_Key();
		if(Disp_Flag == 1)
		{
		 	switch(Page_Idx)
			{
			 	case 0: Disp_All(); break;
				case 1: Disp_Frame(); break;
				case 2:	Disp_Checker0(); break;
				case 3:	Disp_Checker1(); break;
				case 4:	Disp_Q(); break;
				case 5:	Disp_Clip(); break;
			}
			Disp_Flag = 0;
		}
		if(Auto_Flash == 1)
		{
		 	Disp_Flag = 1;
			if(++Page_Idx >= Max_Page) Page_Idx = 0;
			DelayMS(1000);	
		}
	}	
}



