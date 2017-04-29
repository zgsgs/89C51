#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit BEEP = P3^7;

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0x00
};
uchar Pre_KeyNO = 16,KeyNO = 16;

void DelayMS(uint ms)
{
 	uchar t;
	while(ms--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Keys_Scan()
{
 	uchar Tmp;
	P1 = 0x0f;
	DelayMS(1);
	Tmp = P1 ^ 0x0f;
	switch(Tmp)
	{
	 	case 1: KeyNO = 0; break;
		case 2: KeyNO = 1; break;
		case 4: KeyNO = 2; break;
		case 8: KeyNO = 3; break;
		default: KeyNO = 16;
	}
	P1 = 0xf0;
	DelayMS(1);
	Tmp = P1 >> 4 ^ 0x0f;
	switch(Tmp)
	{
	 	case 1: KeyNO += 0; break;
		case 2: KeyNO += 4; break;
		case 4: KeyNO += 8; break;
		case 8: KeyNO += 12;
	}
}

void Beep()
{
 	uchar i;
	for(i=0;i<100;i++)
	{
	 	DelayMS(1);
		BEEP = ~BEEP;
	}
	BEEP = 1;
}

void main()
{
 	P0 = 0x00;
	while(1)
	{
	 	P1 = 0xf0;
		if(P1 != 0xf0)
			Keys_Scan();
		if(Pre_KeyNO != KeyNO)
		{
		 	P0 = ~DSY_CODE[KeyNO];
			Beep();
			Pre_KeyNO = KeyNO;
		}
		DelayMS(100);
	}
}
