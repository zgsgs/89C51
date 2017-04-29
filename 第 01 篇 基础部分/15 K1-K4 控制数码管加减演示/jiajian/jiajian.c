#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff
};
uchar Num_Buffer[] = {0,0,0};
uchar Key_Code,Key_Counts=0;

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
	 	for(t=0;t<120;t++);
	}
}

void Show_Counts_ON_DSY()
{
 	uchar i,j=0x01;
	Num_Buffer[2]=Key_Counts/100;
   	Num_Buffer[1]=Key_Counts/10%10;
	Num_Buffer[0]=Key_Counts%10;
	for(i=0;i<3;i++)
	{
	 	j = _cror_(j,1);
		P2 = j;
		P0 = DSY_CODE[Num_Buffer[i]];
		DelayMS(1);
	}
}

void main()
{
 	uchar i;
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0x00;
	Key_Code = 0xff;
	while(1)
	{
	 	Show_Counts_ON_DSY();
		P1 = 0xff;
		Key_Code = P1;
		if(Key_Code != 0xff)
		{
			for(i=0;i<30;i++)
			{
			 	Show_Counts_ON_DSY();
			}
		}
		switch(Key_Code)
		{
		 	case 0xfe:if(Key_Counts<255) Key_Counts++;break;
			case 0xfd:if(Key_Counts>0)	 Key_Counts--;break;
			case 0xfb:Key_Counts=0;
		}
		Key_Code = 0xff;
	}
}