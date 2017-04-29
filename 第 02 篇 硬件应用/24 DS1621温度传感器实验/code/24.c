/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
bit I2C_Busy, NO_Ack,Bus_Fault,point;

uchar bdata a;
sbit LSB = a^0;
sbit MSB = a^7;
sbit SDA = P3^3;
sbit SCL = P3^2;
uchar Array[] = {'0','1','2','3','4','5','6','7','8','9'};
uchar command_data[]=
{
 	0xac,0x00,0xee,0xa1,0x00,0x00,0xa2,0x00,0x00,0xaa
};
uchar Prompt[]="Waiting for a while...\r";
uchar i;
void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void SendStop()
{
 	SDA = 0;
	SCL = 1;
	_nop_();
	SDA = 1;
	I2C_Busy = 0;
}

void SendByte(uchar wd)
{
 	uchar i;
	a = wd;
	for(i=0;i<8;i++)
	{
	 	SCL = 0;
		_nop_();
		_nop_();
		SDA = MSB;
		a <<= 1;
		_nop_();
		_nop_();
		SCL = 1;
		_nop_();
		_nop_();
		SCL = 0;
	}
	SDA = 1;
	SCL = 1;
	_nop_();
	_nop_();

	if(!SDA)
	{
	 	SCL = 0;
		_nop_();
		_nop_();
	}
	else
	{
	 	NO_Ack = 1;
		SCL = 0;
		_nop_();
		_nop_();
	}
}

void Master(uchar slave_addr)
{

 	I2C_Busy = 1;
	NO_Ack = 0;
	Bus_Fault = 0;
	if(!SCL || !SDA)
		Bus_Fault = 1;
	else
	{
	 	SDA = 0;
		_nop_();
		_nop_();
		SCL = 0;
		_nop_();
		_nop_();
		SendByte(slave_addr);
	}
}

uchar RecvByte(uchar cnt)
{
	uchar i,rcv_data;
	for(i=0;i<8;i++)
	{
	 	SDA = 1;
		SCL = 1;
		_nop_();
		LSB = SDA;
		if(i<7)
			a <<= 1;
		_nop_();
		SCL = 0;
		_nop_();
	} 
	
	if(cnt == 1)
		SDA = 1;
	else
		SDA = 0;
	SCL = 1;
	_nop_();
	SCL = 0;
	SDA = 1;
	_nop_();
	rcv_data = a;
	return rcv_data;	
}

void SendData(uchar slave_address,uchar start,uchar end)
{
 	Master(slave_address);
	for(i=start;i<=end;i++)
		SendByte(command_data[i]);	
	SendStop();
}

void InitialiseSerialPort()
{
 	TMOD = 0x20;
	TH1  = 0xfd;
	SCON = 0x50;
	TR1  = 1;
}

void SendCharToSerialPort(uchar ch)
{
 	SBUF = ch;
	while(!TI);
	TI = 0;
}

void SendTemperatureToSerialPort(uchar val)
{
 	if(val>200)
	{
	 	val = 255-val;
		SendCharToSerialPort('-');
		if(!point)
			val+=1;
	}
	SendCharToSerialPort(Array[(val/10)/10]);
	SendCharToSerialPort(Array[(val/10)%10]);
	SendCharToSerialPort(Array[val%10]);
	SendCharToSerialPort('.');
	if(point)
		SendCharToSerialPort('5');
	else
		SendCharToSerialPort('0');
	SendCharToSerialPort(' ');
	SendCharToSerialPort('C');
	SendCharToSerialPort('\r');	
}

void SetTemperatureLimit(uchar HI,uchar LO)
{
	command_data[4] = HI;
	command_data[5]	= 0;
	command_data[7] = LO;
	command_data[8] = 0;
	SendData(0x90,3,5);
	DelayMS(10);
	SendData(0x90,6,8);	
}

void StartConversion()
{
 	SendData(0x90,2,2);
	DelayMS(750);
}

uchar ReadTemp()
{
 	uchar d;
	SendData(0x90,9,9);
	Master(0x91);
	d = RecvByte(0);
	point = RecvByte(1)>>7;
	SendStop();
	return d;
}

void WriteConfig(uchar c)
{
 	command_data[1] = c;
	SendData(0x90,0,1);		
}

void main()
{
 	uchar i;
   	InitialiseSerialPort();
	while(Prompt[i]!='\0')
		SendCharToSerialPort(Prompt[i++]);
	WriteConfig(0x02);
	StartConversion();
	SetTemperatureLimit(40,35);
	while(1)
	{
	 	DelayMS(50);
		SendTemperatureToSerialPort(ReadTemp());
	}	
}



