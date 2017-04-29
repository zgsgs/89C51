/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P0^0;
sbit LED2 = P0^3;
sbit K1 = P1^0;	  //定义一个按键

void Delay(uint x)	 //延时
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void putc_to_SerialPort(uchar c)  //发送数据
{
 	SBUF = c;	//SBUF寄存器，用于存储数据
	while(TI == 0);	 //数据发送成功时，TI由硬件自动置1
	TI = 0;	  //需要软件手动置0，等待下次数据的到来
}

void main()
{	//I2C通讯初始化
 	uchar Operation_NO = 0;
	SCON = 0x40;
	TMOD = 0x20;
	PCON = 0x00;
	TH1 = 0xfd;	  //设置高八位
	TL1 = 0xfd;	  //设置低八位
	TI = 0;		  //TI发送标志位置0
	TR1 = 1;	  //允许串行通讯
	while(1)
	{
	 	if(K1 == 0)
		{
		 	while(K1==0);
			Operation_NO=(Operation_NO+1)%4;
		}
		switch(Operation_NO)
		{
		 	case 0:
					LED1=LED2=1; break;
			case 1:
					putc_to_SerialPort('A');
					LED1=~LED1;LED2=1;break;
			case 2:
					putc_to_SerialPort('B');
					LED2=~LED2;LED1=1;break;
			case 3:
					putc_to_SerialPort('C');
					LED1=~LED1;LED2=LED1;break;
		}
		Delay(10);
	}
}