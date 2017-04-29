 /***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar Receive_Buffer[101];
uchar Buf_Index = 0;
uchar code DSY_CODE[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00
};

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	uchar i;
	P0 = 0x00;
	Receive_Buffer[0]=i;
	SCON = 0x50;
	TMOD = 0x20;
	PCON = 0x00;
	TH1  = 0xfd;
	TL1  = 0xfd;
	EA   = 1;
	EX0  = 1;
	IT0  = 1;
	ES   = 1;
	IP   = 0x01;
	TR1  = 1;
	while(1)
	{
	 	for(i=0;i<100;i++)
		{
		 	if(Receive_Buffer[i]==-1) 
				break;
			P0 = DSY_CODE[Receive_Buffer[i]];
			Delay(200); 
		}
		Delay(200);
	}
}

void Serial_INT() interrupt 4
{
 	uchar c;
	if(RI==0) 
		return;
	ES = 0;
	RI = 0;
	c  = SBUF;
	if(c>='0' && c<='9')
	{
	 	Receive_Buffer[Buf_Index]=c-'0';
		Receive_Buffer[Buf_Index+1]=-1;
		Buf_Index = (Buf_Index+1)%100;	
	}
	ES = 1;
}

void EX_INT0() interrupt 0
{
 	uchar *s = ("Receiving From 8051...\r\n");
	uchar i = 0;
	while(s[i]!='\0')
	{
	 	SBUF = s[i];
		while(TI == 0);
		TI = 0;
		i++;
	}
}