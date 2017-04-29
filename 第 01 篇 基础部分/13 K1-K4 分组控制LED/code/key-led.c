#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

void DelayMS(uint x)
{
 	uchar t;
	while(x--)
	{
		for(t=0;t<120;t--);
	}
}

void main()
{
 	uchar k,t,Key_State;
	P0 = 0xff;
	P1 = 0xff;
	while(1)
	{
	 	t = P1;
		{
		 	DelayMS(10);
			if(t != P1)
				continue;
			Key_State = ~t >> 4;
			k = 0;
			while(Key_State != 0)
			{
			 	k++;
				Key_State >>= 1;
			}
			switch(k)
			{
			 	case 1: if(P0 == 0x00)
						P0 = 0xff;
						P0 <<= 1;
						DelayMS(200);
						break;
				case 2: P0 = 0xf0;
						break;
				case 3: P0 = 0x0f;
						break;
				case 4: P0 = 0xff;
			}
		}
	}
}