/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <string.h>
#define uchar unsigned char
#define uint unsigned int
void Initialize_LCD();
void ShowString(uchar,uchar,uchar *);
sbit K1 = P3^0;
sbit K2 = P3^1;
sbit K3 = P3^2;

uchar code Prompt[]="PRESS K1--K4 TO START DEMO PROG";
uchar const Line_Count = 6;
uchar code Msg[][80]=
{
 	"Many CAD users dismiss",
	"process of creating PCB",
	"of view.with PCB layout",
	"placement and track routing,",
	"can often be the most time",
	"And if you use circuit simulation",
	"you are going to spend even more"
};
uchar Disp_Buffer[32];
void Delayxms(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void V_Scroll_Display()
{
 	uchar i,j,k = 0;
	uchar *p = Msg[0];
	uchar *q = Msg[Line_Count] + strlen(Msg[Line_Count]);
	while(p<q)
	{
	 	for(i=0;(i<16)&&(p<q);i++)
		{
		 	if(((i==0)||(i==15))&& *p == ' ')
				p++;
			if(*p != '\0')
			{
			 	Disp_Buffer[i] = *p++;
			}
			else
			{
			 	if(++k>Line_Count)
					break;
				p = Msg[k];
				Disp_Buffer[i] = *p++;
			}
		}
		for(j=i;j<16;j++)
			Disp_Buffer[j]=' ';
		while(F0)
			Delayxms(5);
		ShowString(0,0,"      ");
		Delayxms(150);
		while(F0)
			Delayxms(5);
		ShowString(0,1,Disp_Buffer);
		Delayxms(150);
		while(F0)
			Delayxms(5);
		ShowString(0,0,Disp_Buffer);
		ShowString(0,1,"      ");
		Delayxms(150);	
	}
	ShowString(0,0,"         ");
	ShowString(0,1,"         ");
}

void H_Scroll_Display()
{
	uchar m,n,t = 0,L=0;
	uchar *p = Msg[0];
	uchar *q = Msg[Line_Count] + strlen(Msg[Line_Count]);
	for(m=0;m<16;m++)
			Disp_Buffer[m]=' ';	
	while(p<q)
	{
	 	if((m=16||m==31)&& *p == ' ')
			p++;
		for(m=16;m<32&&p<q;m++)
		{
		 	if(*p != '\0')
			{
				Disp_Buffer[m] = *p++; 	
			}
			else
			{
			 	if(++t>Line_Count)
					break;
				p = Msg[t];
				Disp_Buffer[m] = *p++;
			}
		}
		for(n=m;n<32;n++)
			Disp_Buffer[n]=' ';
		for(m=0;m<=16;m++)
		{
		 	while(F0)
		 		Delayxms(5);
		   	ShowString(0,L,Disp_Buffer+1);
		   	while(F0)
		 		Delayxms(5);
			Delayxms(20);
		}
		L = (L==0)? 1:0;
		Delayxms(200);
	}
	if(L==1)
		ShowString(0,1,"      ");	
}

void EX_INT0() interrupt 0
{
 	F0 = !F0;
}

void main()
{
 	uint Count = 0;
	IE = 0x81;
	IT0 = 1;
	F0  = 0;
	Initialize_LCD();
	ShowString(0,0,Prompt);
	ShowString(0,1,Prompt+16);
	while(1)
	{
	 	if(K1 == 0)
		{
		 	V_Scroll_Display();
			Delayxms(200);
		}
		else if(K2 == 0)
		{
		 	H_Scroll_Display();
			Delayxms(200);	
		}
	}
}