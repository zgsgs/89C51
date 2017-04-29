/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P1^0;
sbit LED2 = P1^3;
sbit K1 = P1^7;
uchar Operation_NO = 0;
uchar code DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void putc_to_SerialPort(uchar c)
{
 	SBUF = c;
	while(TI == 0);
	TI = 0;
}

void main()
{
 	LED1=LED2=1;
	P0 = 0x00;
	SCON = 0x50;
	TMOD = 0x20;
	PCON = 0x00;
	TH1  = 0xfd;
	TL1  = 0xfd;
	TI   = 0;
	RI   = 0;
	TR1  = 1;
	IE   = 0x90;
	while(1)
	{
	 	Delay(100);
		if(K1 == 0)
		{
		 	while(K1==0);
			Operation_NO=(Operation_NO+1)%4;
			switch(Operation_NO)
			{
			 	case 0:
						putc_to_SerialPort('X');
						LED1=LED2=1; break;
				case 1:
						putc_to_SerialPort('A');
						LED1=0;LED2=1;break;
				case 2:
						putc_to_SerialPort('B');
						LED2=0;LED1=1;break;
				case 3:
						putc_to_SerialPort('C');
						LED1=0;LED2=0;break;
			}
		}
	}
}

void Serial_INT() interrupt 4
{
 	if(RI)
	{
	 	RI = 0;
		if(SBUF>=0&&SBUF<=9)
			P0 = DSY_CODE[SBUF];
		else 
			P0 = 0x00;
	}
}