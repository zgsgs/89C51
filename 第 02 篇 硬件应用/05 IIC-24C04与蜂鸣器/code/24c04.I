
#line 1 "24c04.c" /0
  
#line 1 "C:\KEIL\C51\INC\REG52.H" /0






 
 
 
 
 
 
 sfr P0    = 0x80;
 sfr P1    = 0x90;
 sfr P2    = 0xA0;
 sfr P3    = 0xB0;
 sfr PSW   = 0xD0;
 sfr ACC   = 0xE0;
 sfr B     = 0xF0;
 sfr SP    = 0x81;
 sfr DPL   = 0x82;
 sfr DPH   = 0x83;
 sfr PCON  = 0x87;
 sfr TCON  = 0x88;
 sfr TMOD  = 0x89;
 sfr TL0   = 0x8A;
 sfr TL1   = 0x8B;
 sfr TH0   = 0x8C;
 sfr TH1   = 0x8D;
 sfr IE    = 0xA8;
 sfr IP    = 0xB8;
 sfr SCON  = 0x98;
 sfr SBUF  = 0x99;
 
 
 sfr T2CON  = 0xC8;
 sfr RCAP2L = 0xCA;
 sfr RCAP2H = 0xCB;
 sfr TL2    = 0xCC;
 sfr TH2    = 0xCD;
 
 
 
 
 sbit CY    = PSW^7;
 sbit AC    = PSW^6;
 sbit F0    = PSW^5;
 sbit RS1   = PSW^4;
 sbit RS0   = PSW^3;
 sbit OV    = PSW^2;
 sbit P     = PSW^0;  
 
 
 sbit TF1   = TCON^7;
 sbit TR1   = TCON^6;
 sbit TF0   = TCON^5;
 sbit TR0   = TCON^4;
 sbit IE1   = TCON^3;
 sbit IT1   = TCON^2;
 sbit IE0   = TCON^1;
 sbit IT0   = TCON^0;
 
 
 sbit EA    = IE^7;
 sbit ET2   = IE^5;  
 sbit ES    = IE^4;
 sbit ET1   = IE^3;
 sbit EX1   = IE^2;
 sbit ET0   = IE^1;
 sbit EX0   = IE^0;
 
 
 sbit PT2   = IP^5;
 sbit PS    = IP^4;
 sbit PT1   = IP^3;
 sbit PX1   = IP^2;
 sbit PT0   = IP^1;
 sbit PX0   = IP^0;
 
 
 sbit RD    = P3^7;
 sbit WR    = P3^6;
 sbit T1    = P3^5;
 sbit T0    = P3^4;
 sbit INT1  = P3^3;
 sbit INT0  = P3^2;
 sbit TXD   = P3^1;
 sbit RXD   = P3^0;
 
 
 sbit SM0   = SCON^7;
 sbit SM1   = SCON^6;
 sbit SM2   = SCON^5;
 sbit REN   = SCON^4;
 sbit TB8   = SCON^3;
 sbit RB8   = SCON^2;
 sbit TI    = SCON^1;
 sbit RI    = SCON^0;
 
 
 sbit T2EX  = P1^1;  
 sbit T2    = P1^0;  
 
 
 sbit TF2    = T2CON^7;
 sbit EXF2   = T2CON^6;
 sbit RCLK   = T2CON^5;
 sbit TCLK   = T2CON^4;
 sbit EXEN2  = T2CON^3;
 sbit TR2    = T2CON^2;
 sbit C_T2   = T2CON^1;
 sbit CP_RL2 = T2CON^0;
 
 
#line 1 "24c04.c" /0
 
  
#line 1 "C:\KEIL\C51\INC\INTRINS.H" /0






 
 
 
 
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 
#line 2 "24c04.c" /0
 
 
 
 
 
 sbit SCL = P1^0;
 sbit SDA = P1^1;
 sbit SPK = P3^0;
 
  unsigned char code HI_LIST[] =
 {
 0,226,229,232,233,236,238,240,241,242,245,246,247,248
 };
  unsigned char code LO_LIST[] =
 {
 0,4,13,10,20,3,8,6,2,23,5,26,1,4,3
 };
  unsigned char code Song_24C04[] =
 {
 1,2,3,1,1,2,3,1,3,4,5,3,4,5
 };
  unsigned char sidx;
 
 void DelayMS(unsigned int x)
 {
  unsigned char t;
 while(x--)
 {
 for(t=120;t>0;t--);
 }
 }
 
 void Start()
 {
 SDA=1;SCL=1;{_nop_();_nop_();_nop_();_nop_();};SDA=0;{_nop_();_nop_();_nop_();_nop_();};SCL=0;
 }
 
 void Stop()
 {
 SDA=0;SCL=0;{_nop_();_nop_();_nop_();_nop_();};SCL=1;{_nop_();_nop_();_nop_();_nop_();};SDA=1;
 }
 
 void RACK()
 {
 SDA=1;{_nop_();_nop_();_nop_();_nop_();};SCL=1;{_nop_();_nop_();_nop_();_nop_();};SCL=0;
 }
 
 void NO_ACK()
 {
 SDA=1;SCL=1;{_nop_();_nop_();_nop_();_nop_();};SCL=0;SDA=0;
 }
 
 void Write_A_Byte(unsigned char b)
 {
  unsigned char i;
 for(i=0;i<8;i++)
 {
 b<<=1;SDA=CY;_nop_();SCL=1;{_nop_();_nop_();_nop_();_nop_();};SCL=0;
 }
 RACK();
 }
 
 void Write_IIC(unsigned char addr,unsigned char dat)
 {
 Start();
 Write_A_Byte(0xa0);
 Write_A_Byte(addr);
 Write_A_Byte(dat);
 Stop();
 DelayMS(10);
 }
 
  unsigned char Read_A_Byte()
 {
  unsigned char i,b;
 for(i=0;i<8;i++)
 {
 SCL=1;b<<=1;B|=SDA;SCL=0;
 }
 return b;
 }
 
  unsigned char Read_Current()
 {
  unsigned char d;
 Start();
 Write_A_Byte(0xa1);
 d=Read_A_Byte();
 NO_ACK();
 Stop();
 return d;
 }
 
  unsigned char Random_Read(unsigned char addr)
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
  unsigned char i;
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
