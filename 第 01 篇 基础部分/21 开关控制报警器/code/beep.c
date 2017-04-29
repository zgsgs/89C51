#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit SPK = P1^0;
sbit K1 = P1^7;

void Alarm(uchar t)
{
 	uchar i,j;
	for(i=0;i<200;i++)
	{
	 	SPK = ~SPK;
		for(j=0;j<t;j++);
	}
}

void main()
{
 	while(1)
	{
	 	if(K1==1)
		{
		 	Alarm(90);
			Alarm(120);
		}
	}
}