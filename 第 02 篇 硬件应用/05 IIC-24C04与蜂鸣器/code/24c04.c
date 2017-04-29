#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define NOP4() {_nop_();_nop_();_nop_();_nop_();}

sbit SCL = P1^0;
sbit SDA = P1^1;
sbit SPK = P3^0;

uchar code HI_LIST[] =
{
 	0,226,229,232,233,236,238,240,241,242,245,246,247,248
};
uchar code LO_LIST[] =
{
 	0,4,13,10,20,3,8,6,2,23,5,26,1,4,3
};
uchar code Song_24C04[] =
{
 	1,2,3,1,1,2,3,1,3,4,5,3,4,5
};
uchar sidx;

void DelayMS(uint x)
{
	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Start()
{
 	SDA=1;SCL=1;NOP4();SDA=0;NOP4();SCL=0;
}

void Stop()
{
 	SDA=0;SCL=0;NOP4();SCL=1;NOP4();SDA=1;
}

void RACK()
{
 	SDA=1;NOP4();SCL=1;NOP4();SCL=0;
}

void NO_ACK()
{
 	SDA=1;SCL=1;NOP4();SCL=0;SDA=0;
}

void Write_A_Byte(uchar b)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	b<<=1;SDA=CY;_nop_();SCL=1;NOP4();SCL=0;
	}
	RACK();
}

void Write_IIC(uchar addr,uchar dat)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(addr);
	Write_A_Byte(dat);
	Stop();
	DelayMS(10);
}

uchar Read_A_Byte()
{
 	uchar i,b;
	for(i=0;i<8;i++)
	{
	 	SCL=1;b<<=1;B|=SDA;SCL=0;
	}
	return b;
}

uchar Read_Current()
{
 	uchar d;
	Start();
	Write_A_Byte(0xa1);
	d=Read_A_Byte();
	NO_ACK();
	Stop();
	return d;
}

uchar Random_Read(uchar addr)
{
 	Start();
	Write_A_Byte(0xa0);
	Write_A_Byte(addr);
	Stop();
	return Read_Current();		
}

void T0_INT() interrupt 1
{
 	SPK=!SPK;
	TH0=HI_LIST[sidx];
	TL0=LO_LIST[sidx];
}

void main()
{
 	uchar i;
	IE=0x82;
	TMOD=0x00;
	for(i=0;i<14;i++)
	{
	 	Write_IIC(i,Song_24C04[i]);	
	}
	while(1)
	{
	 	for(i=0;i<14;i++)
		{
		 	sidx=Random_Read(i);
			TR0=1;
			DelayMS(300);
		}
	}
}