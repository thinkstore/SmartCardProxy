#include "conv.h"
/* Example */
/* uchar src[]={0x12 , 0x34 };*/
/* uchar dst[10];*/
/* hex2str( dst , src , 2); */
/* dst = "1234" */
int hex2str( uchar* dst , uchar* src , int len )
{
     uchar i;
     for(i=0 ; i<len ; i++)
     {
          dst[2*i]   = ((src[i] & 0xF0 ) >> 4 ) + 0x30;
          dst[2*i+1] = ((src[i] & 0x0F )  ) + 0x30;
          dst[2*i+2] = 0;
     }
     return strlen((char*)dst);
}
uchar ascii2hex_uchar( char c)
{
     if(c >= 0x41)
          return (c-0x07)&0x0F;

     return c&0x0F;
}


/* Example	: src = "1AC4B2"*/
/*                  dst = "\x1A\xC4\xB2" */

int str2hex( uchar* dst , const char* src )
{
     int len , i;
     len = strlen( src );

     if( len%2 ) return 0;
     
     for(i=0 ; i<len ; i++)
     {
          if( src[i] <'0' ||  src[i] > 'F')
               return 0;
     }

     char tmp1 ;
     char tmp2;
     uchar tmp3 ;
     
     for(i=0 ; i<len ; i+=2 )
     {
          tmp1 = ascii2hex_uchar(src[i])  ;
          tmp2 = ascii2hex_uchar(src[i+1])  ;
          tmp3 = (tmp1 & 0x0f) << 4 | (tmp2 & 0x0f);
          dst[i/2] = tmp3;
     }
     return i/2;
}
int str2bcd( uchar* dst , const char* src )
{
     int pos=0;
     while( src[pos])
     {
          if((src[pos] < '0') || (src[pos] > '9'))
               return 0;
          pos++;
     }
     return str2hex( dst , src);
}

// Example	: ptSrc = 1234567890

// if lgDest = 2	ptDest = 0x78/0x90
// if lgDest = 7	ptDest = 0x00/0x00/0x12/0x34/0x56/0x78/0x90
int long2bcd(unsigned long src , uchar* dst,int dst_len )
{
     char ascii_temp[2+1];
     int  pos=0;
     uchar tmp=0;
     
     memset( dst  , 0 , dst_len);
     do
     {
          memset(ascii_temp , 0 , sizeof(ascii_temp));
          sprintf( ascii_temp , "%02u" , (unsigned short)(src % 100));
          pos += str2hex( &dst[pos] , ascii_temp);
     }while( (unsigned long)(src /= (unsigned long)100)>0) ;

     for( int i=0 ; i < dst_len/2 ; i++ )
     {
          tmp        = dst[i];
          dst[i]     = dst[dst_len-i-1];
          dst[dst_len-i-1] = tmp;
     }
     return pos;
}

unsigned long bcd2long( uchar* src , int len )
{
     uchar ascii_tmp[20+1];

     memset(ascii_tmp , 0 , sizeof(ascii_tmp));
     hex2str( ascii_tmp , src , len);
     return atoi((const char*)ascii_tmp);
     
}




static const unsigned short CrcTable[ 256 ] = { 
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 
    0xD1AD,  0xE1CE, 0xF1EF, 0x1231,  0x0210, 0x3273,  0x2252, 0x52B5, 0x4294,  0x72F7, 0x62D6, 0x9339,  0x8318, 
    0xB37B, 0xA35A, 0xD3BD, 0xC39C,  0xF3FF, 0xE3DE,  0x2462,  0x3443, 0x0420, 0x1401,  0x64E6,  0x74C7,  0x44A4, 
    0x5485, 0xA56A,  0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF,  0xC5AC, 0xD58D, 0x3653,  0x2672, 0x1611, 0x0630, 
    0x76D7,  0x66F6, 0x5695,  0x46B4, 0xB75B,  0xA77A, 0x9719, 0x8738,  0xF7DF, 0xE7FE, 0xD79D,  0xC7BC, 0x48C4, 
    0x58E5, 0x6886, 0x78A7,  0x0840,  0x1861, 0x2802, 0x3823, 0xC9CC,  0xD9ED,  0xE98E,  0xF9AF, 0x8948,  0x9969, 
    0xA90A, 0xB92B, 0x5AF5,  0x4AD4,  0x7AB7,  0x6A96, 0x1A71,  0x0A50, 0x3A33,  0x2A12, 0xDBFD, 0xCBDC,  0xFBBF, 
    0xEB9E, 0x9B79, 0x8B58,  0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03,  0x0C60, 0x1C41, 
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 
    0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78, 0x9188, 0x81A9, 
    0xB1CA,  0xA1EB, 0xD10C,  0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3,  0x5004, 0x4025,  0x7046, 
    0x6067, 0x83B9, 0x9398,  0xA3FB,  0xB3DA, 0xC33D,  0xD31C, 0xE37F, 0xF35E, 0x02B1, 0x1290,  0x22F3, 0x32D2, 
    0x4235,  0x5214, 0x6277, 0x7256, 0xB5EA,  0xA5CB, 0x95A8, 0x8589, 0xF56E,  0xE54F, 0xD52C, 0xC50D, 0x34E2, 
    0x24C3, 0x14A0, 0x0481,  0x7466, 0x6447,  0x5424, 0x4405,  0xA7DB, 0xB7FA, 0x8799,  0x97B8,  0xE75F,  0xF77E, 
    0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676,  0x4615, 0x5634, 0xD94C,  0xC96D, 0xF90E, 
    0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,  0x5844, 0x4865,  0x7806, 0x6827,  0x18C0,  0x08E1,  0x3882, 0x28A3, 
    0xCB7D,  0xDB5C,  0xEB3F, 0xFB1E,  0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 
    0x1AD0, 0x2AB3, 0x3A92, 0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07, 
    0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 
    0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0}; 
 
unsigned short CalculateCRC ( unsigned char *Buffer, unsigned int Len ) 
{ 
    unsigned short Crc = 0xffff; 
   
    while (Len--) 
    {  
        Crc = CrcTable[ ((Crc >> 8) ^ *Buffer++) ] ^ (Crc << 8); 
    } 
    return(Crc); 
} 

unsigned short Pla_CCITT_CRC16(unsigned short u16ValInit, unsigned short u16PolyCRC16, unsigned char *pu8Data, unsigned short u16LenData)
{
    unsigned short u16Pos=0, j, v, xor_flag;
    unsigned short	u16CRC16, u16RetCRC16;

	//u16CRC16 = 0xFFFF ;
    u16CRC16 = u16ValInit;

    for (u16Pos=0; u16Pos < u16LenData; u16Pos++)
    {
        v = 0x80;

    	for (j=0; j < 8; j++)
    	{
            if (u16CRC16 & 0x8000)
            {
            	xor_flag = 1;
            }
            else
            {
            	xor_flag = 0;
            }

            u16CRC16 <<= 1;

            if (pu8Data[u16Pos] & v)
            {
                u16CRC16 ++;
            }

            if (xor_flag)
            {
            	u16CRC16 ^= u16PolyCRC16;
            }

            v >>= 1;
        }
    }

    for (u16Pos = 0; u16Pos < 16; u16Pos++)
    {
        if (u16CRC16 & 0x8000)
        {
            xor_flag = 1;
        }
        else
        {
            xor_flag = 0;
        }

        u16CRC16 <<= 1;

        if (xor_flag)
        {
            u16CRC16 ^= u16PolyCRC16;
        }
    }

    u16RetCRC16 = 0;
    u16RetCRC16 = (u16CRC16 % 256) * 256;
    u16RetCRC16 += (u16CRC16 / 256);

    return(u16RetCRC16) ;
}
