#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

void main()
{
 	uchar T_Count = 0;
	P0 = 0xfe;
	P2 = 0xfe;
	TMOD = 0x01;
	TH0  = (65535-40000)/256;
	TL0  = (65535-40000)%256;
	TR0  = 1;
	while(1)
	{
	 	if(TF0 == 1)
		{
		 	TF0 = 0;
			TH0  = (65535-40000)/256;
			TL0  = (65535-40000)%256;
			if(++T_Count == 100)
			{
	 			P0 = _crol_(P0,1);
				P2 = _crol_(P2,1);
				T_Count = 0;
			}
		}
	}
}
