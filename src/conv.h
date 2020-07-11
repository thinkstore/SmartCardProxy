#ifndef __CONV_H__
#define __CONV_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TBuffer.h"

int hex2str( uchar* dst , uchar* src , int len );
int str2hex( uchar* dst , const char* src );
int long2bcd(unsigned long src , uchar* dst,int dst_len );
int str2bcd( uchar* dst , const char* src );
unsigned long bcd2long( uchar* src , int len );
//void Trace( unsigned short debug_type , char *base, ...);
unsigned short CalculateCRC ( unsigned char *Buffer, unsigned int Len ) ;
unsigned short Pla_CCITT_CRC16(unsigned short u16ValInit, unsigned short u16PolyCRC16, unsigned char *pu8Data, unsigned short u16LenData);

#endif 
     
