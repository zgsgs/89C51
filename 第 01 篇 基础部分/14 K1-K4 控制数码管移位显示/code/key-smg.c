#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff
};
uchar code DSY_Index[]=
{
  	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
};
uchar Display_Buffer[]=
{
 	0,10,10,10,10,10,10,10
};

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Show_Count_ON_DSY()
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	P2 = DSY_Index[i];
		P0 = DSY_CODE[Display_Buffer[i]];
		DelayMS(2);
	}
}

void main()
{
 	uchar i;
	uchar Key_NO,Key_Counts=0;
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0x00;
	while(1)
	{
	 	Show_Count_ON_DSY();
		P1 = 0xff;
		Key_NO = P1;
		switch(Key_NO)
		{
		 	case 0xfe: Key_Counts++;
						if(Key_Counts>8)
							Key_Counts = 8;
						Display_Buffer[Key_Counts-1] = Key_Counts;
						break;
			case 0xfd: if(Key_Counts>0)
							Display_Buffer[--Key_Counts] = 10;
						if(Key_Counts==0)	
						Display_Buffer[0] = 0;
						break;
			case 0xfb: Display_Buffer[0]=0;
						for(i=1;i<8;i++)
							Display_Buffer[i] = 10;
						Key_Counts = 0;
		}
		while(P1 != 0xff)
			Show_Count_ON_DSY();
	}
}