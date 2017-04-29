/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar code prompts[]=" Serial LCD DEMO ";

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void putc_to_LCD(uchar c)
{
 	SBUF = c;
	while(TI == 0);
	TI = 0;
}

uchar getc_from_terminal()
{
 	while(RI == 0);
	RI = 0;
	return SBUF;
}

void wrcmd(uchar comm)
{
 	putc_to_LCD(0xfe);
	putc_to_LCD(comm);
}

void main()
{
 	uchar i=0,c;
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	RI = 0;
	TI = 0;
	TR1 = 1;
	DelayMS(200);
	while(prompts[i] != '\0')
	{
	 	putc_to_LCD(prompts[i+1]);
		DelayMS(5);
	}
	wrcmd(0xc0);
	wrcmd(0x0d);
	DelayMS(120);
	while(1)
	{
	 	c = getc_from_terminal();
		if(c==0x0d)
		{
		 	wrcmd(0x01);
			continue;
		}
		if(c==0x08)
		{
		 	wrcmd(0x10);
			continue;
		}
		putc_to_LCD(c);
		DelayMS(200);
	}
}