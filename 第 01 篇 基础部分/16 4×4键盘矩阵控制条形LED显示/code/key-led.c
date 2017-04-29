#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0x00
};
uchar code KeyCodeTable[]=
{
  	0x11,0x12,0x14,0x18,0x21,0x22,0x24,0x28,0x41,0x42,0x44,0x48,0x81,0x82,0x84,0x88
};

void Delay()
{
 	uchar i;
	for(i=0;i<200;i++);
}

uchar Keys_Scan()
{
 	uchar sCode,kCode,i,k;
	P1 = 0xf0;
	if((P1&0xf0)!=0xf0)
	{
	 	Delay();
		if((P1&0xf0)!=0xf0)
		{
		 	sCode = 0xfe;
			for(k=0;k<4;k++)
			{
			 	P1 = sCode;
				if((P1&0xf0)!=0xf0)
				{
				 	kCode = ~P1;
					for(i=0;i<16;i++)
					{
					 	if(kCode == KeyCodeTable[i])
							return i;
					}
				}
				else 
					sCode = _crol_(sCode,1);
			}
		}
	}
	return -1;
}

void main()
{
 	uchar KeyNO = -1;
	uchar i,P2_LED,P3_LED;
	while(1)
	{
	 	KeyNO = Keys_Scan();
		if(KeyNO != -1)
		{
		 	P2_LED = 0xff;
			P3_LED = 0xff;
			for(i=0;i<=KeyNO;i++)
			{
			 	if(i<8)
					P3_LED>>=1;
				else
					P2_LED>>=1;
			}
			P3 = P3_LED;
			P2 = P2_LED;
		}
	}
}