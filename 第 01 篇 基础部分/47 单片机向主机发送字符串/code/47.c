/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

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

void puts_to_SerialPort(uchar *s)
{
 	while(*s != '\0')
	{
	 	putc_to_SerialPort(*s);
		s++;
		Delay(5);	
	}
}

void main()
{
 	uchar c = 0;
	SCON = 0x40;
	TMOD = 0x20;
	PCON = 0x00;
	TH1  = 0xfd;
	TL1  = 0xfd;
	TI   = 0;
	TR1  = 1;
	Delay(200);
	puts_to_SerialPort("Receiving From 8051...\r\n");
	puts_to_SerialPort("------------------------------\r\n");
	Delay(50);
	while(1)
	{
		putc_to_SerialPort(c+'A');
		Delay(100);
		putc_to_SerialPort(' '); //这个地方‘’间只能有且必须有一个空格
		Delay(100);
		if(c==25)
		{
		 	puts_to_SerialPort("\r\n---------------------------\r\n");
			Delay(100);
		}
		c = (c+1)%26;
		if(c%10==0)
		{
		 	puts_to_SerialPort("\r\n");
			Delay(100);
		}
	}
}