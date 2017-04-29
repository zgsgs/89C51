#include <at89x52.h>
#include <intrins.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <absacc.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char
#define STX 0x02
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define BS  0x08
#define CR  0x0d
#define LF  0x0a
#define DLE 0x10
#define ETB 0x17
#define SPACE 0x20
#define COMMA 0x2c
#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

#define LCMDW XBYTE[0x8000]
#define LCMCW XBYTE[0x8100]
#define DISRAM_SIZE 0x7fff
#define TXTSTART 0x0000
#define GRSTART 0x6800
#define CGRAMSTART 0x7800

#define LC_CUR_POS 0x21
#define LC_CGR_POS 0x22
#define LC_ADD_POS 0x24
#define LC_TXT_STP 0x40
#define LC_TXT_WID 0x41
#define LC_GRH_STP 0x42
#define LC_GRH_WID 0x43
#define LC_MOD_OR  0x80
#define LC_MOD_XOR 0x81
#define LC_MOD_AND 0x82
#define LC_MOD_TCH 0x83
#define LC_DIS_SW  0x90

#define LC_CUR_SHP 0xa0
#define LC_AUT_WR  0xb0
#define LC_AUT_RD  0xb1
#define LC_AUT_OVR 0xb2
#define LC_INC_WR  0xc0
#define LC_INC_RD  0xc1
#define LC_DEC_WR  0xc2
#define LC_DEC_RD  0xc3
#define LC_NOC_WR  0xc4
#define LC_NOC_RD  0xc5
#define LC_SCN_RD  0xe0
#define LC_INC_CP  0xe8
#define LC_BIT_OP  0xf0




 