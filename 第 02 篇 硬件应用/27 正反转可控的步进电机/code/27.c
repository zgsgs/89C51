/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar code FFW[]=
{
 	0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09
};

uchar code REV[]=
{
 	0x09,0x08,0x0c,0x04,0x06,0x02,0x03,0x01
};

sbit K1 = P3^0;
sbit K2 = P3^1;
sbit K3 = P3^2;

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void SETP_MOTOR_FFW(uchar n)
{
 	uchar i,j;
	for(i=0;i<5*n;i++)
	{
	 	for(j=0;j<8;j++)
		{
		 	if(K3 == 0)	break;
			P1 = FFW[j];
			DelayMS(25);
		}
	}
}

void SETP_MOTOR_REV(uchar n)
{
 	uchar i,j;
	for(i=0;i<5*n;i++)
	{
	 	for(j=0;j<8;j++)
		{
		 	if(K3 == 0)	break;
			P1 = REV[j];
			DelayMS(25);
		}
	}
}

void main()
{
 	uchar N = 3;
	while(1)
	{
	 	if(K1 == 0)
		{
		 	P0 = 0xfe;
			SETP_MOTOR_FFW(N);
			if(K3 == 0) break;
		}
		else if(K2 == 0)
		{
		 	P0 = 0xfd;
			SETP_MOTOR_REV(N);
			if(K3 == 0) break;
		}
		else
		{
		 	P0 = 0xfb;
			P1 = 0x03;
		}
	}
}