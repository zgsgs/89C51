#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit BEEP = P3^7;
uchar code SONG_TONE[]=
{
 	212,212,190,212,159,169,212,212,190,212,142,159,212,212,106,126,129,169,190,119,119,126,159,142,159,0
};
uchar code SONG_LONG[]=
{
 	9,3,12,12,12,24,9,3,12,12,12,24,9,3,12,12,12,12,12,9,3,12,12,12,24,0
};

void DelayMS(uint ms)
{
 	uchar t;
	while(ms--)
	{
	 	for(t=0;t<120;t++);
	}
}

void PlayMusic()
{
 	uint i =0,j,k;
	while(SONG_LONG[i]!=0||SONG_TONE[i]!=0)
	{
	 	for(j=0;j<SONG_LONG[i]*20;j++)
		{
		 	BEEP = ~BEEP;
			for(k=0;k<SONG_TONE[i]/3;k++);
		}
		DelayMS(10);
		i++;
	}
}

void main()
{
 	while(1)
	{
	 	PlayMusic();
		DelayMS(500);
	}
}