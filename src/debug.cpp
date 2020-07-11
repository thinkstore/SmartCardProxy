#include "debug.h"
#include "stdlib.h"
#include "tprintf.h"
#include <stdarg.h>
#include <QTextEdit>
#include <QByteArray>

// unsigned long trace_window = 0;
// unsigned long apdu_window  = 0;


// void set_apdu_window( wxTextCtrl* win )
// {
    // apdu_window = (unsigned long)win;
// }

// void set_trace_window( wxTextCtrl* win )
// {
    // trace_window = (unsigned long)win;
// }

// wxTextCtrl* get_trace_window( wxTextCtrl* win )
// {
//     return (wxTextCtrl*)trace_window;
// }

#define ucharS_IN_A_LINE   24


void zldump(FILE* output , unsigned char* line_addr , int len )
{
    int i;
    unsigned char c;
    unsigned char pos=0;
    unsigned char line_buffer[300+1];
          
    if(len > 0 )
    {
        len = ( ucharS_IN_A_LINE < len ) ? ucharS_IN_A_LINE : len ;
        for(i=0 ; i < len ; i++ )
        {
            sprintf( (char*)&line_buffer[pos],  "%02X " , line_addr[i] & 0xFF  );
            pos += 3;
        }
               
        for(i=len ; i < ucharS_IN_A_LINE ; i++ )
        {
            strcat( (char*)&line_buffer[pos] , "   " );
            pos += 3;
        }
               
        for( i=0 ; i < len ; i++ )
        {
            c = line_addr[i] & 0x7f ;

            if( c < 32 )
                c = '.';

            if( c > 127 )
                c = '.';
            
            if( c == '%' )
                c = '.';

            sprintf( (char*)&line_buffer[pos] , "%c" , c );
            pos++;
        }
        zprint(0 ,output, (char*)line_buffer);
    }
          
}
void zmdump( FILE* output , unsigned char* data , int len )
{
    int i;
    for(i =0 ; i <= len ; i+=ucharS_IN_A_LINE )
    {
        zldump( output , &data[i] , (ucharS_IN_A_LINE < (len - i)) ? ucharS_IN_A_LINE : len - i );
    }
}
void ztrace( unsigned char cond , FILE* output , char* descr , unsigned char* data , int len )
{
    if(cond)
    {
        if( len > 0 )
        {
            if( descr ) zprint( 0 , output , "%s Len : [%d]" , descr , len );
            zmdump( output , data , len );
        }
    }
}
void zprint( unsigned short flags ,FILE* output , char* base , ... )
{
    // unsigned char len = 0 ;
    // char buffer[48+1];
    
    va_list args;
    unsigned char sTmp[300+1];
#ifdef WIN32
    unsigned char i;
#endif

    memset( sTmp , 0 , sizeof(sTmp));
    va_start(args, base);

#ifdef __GNUC__
    vsprintf((char *)sTmp, (char*)base, args);
#else
    vsprintf((char *)sTmp, (char*)base, args);
#endif

    va_end(args);

#ifdef WIN32 
    for( i = 0 ; i < strlen((char*)sTmp) ; i++ )
    {
        switch( sTmp[i] )
        {
            case 253:
                sTmp[i] = 'u';
                break;
            case 199:
                sTmp[i] = 'C';
                break;
            case 214:
                sTmp[i] = 'O';
                break;
            case 208:
                sTmp[i] = 'G';
                break;
            case 221:
                sTmp[i] = 'I';
                break;
            case 220:
                sTmp[i] = 'U';
                break;
            case 231:
                sTmp[i] = 'c';
                break;
            case 246:
                sTmp[i] = 'o';
                break;
            case 222:
                sTmp[i] = 'S';
                break;
            case 254:
                sTmp[i] = 's';
                break;
        }
    }
#endif
    if( strlen( (char*)sTmp ) == 0 )  return ;
    
    if( output == stdout )
    {
        tprintf( (const char*)sTmp );
    }
    else 
    {
        ((QPlainTextEdit*)output)->appendPlainText( QString((const char*)sTmp) );
        // ((wxTextCtrl*)output)->AppendText( sTmp );
        // ((wxTextCtrl*)output)->AppendText( "\n" );
        // ((wxTextCtrl*)output)->ShowPosition( ((wxTextCtrl*)output)->GetLastPosition() );
        // CHECKLIST : zprint calisirligi kontrol ve test edilmeli .
    }
}

QString zldump(unsigned char* line_addr , int len )
{
    int i;
    unsigned char c;
    unsigned char pos=0;
    unsigned char line_buffer[300+1];

    if(len > 0 )
    {
        len = ( ucharS_IN_A_LINE < len ) ? ucharS_IN_A_LINE : len ;
        for(i=0 ; i < len ; i++ )
        {
            sprintf( (char*)&line_buffer[pos],  "%02X " , line_addr[i] & 0xFF  );
            pos += 3;
        }
               
        for(i=len ; i < ucharS_IN_A_LINE ; i++ )
        {
            strcat( (char*)&line_buffer[pos] , "   " );
            pos += 3;
        }
               
        for( i=0 ; i < len ; i++ )
        {
            c = line_addr[i] & 0x7f ;

            if( c < 32 )
                c = '.';

            if( c > 127 )
                c = '.';
            
            if( c == '%' )
                c = '.';

            sprintf( (char*)&line_buffer[pos] , "%c" , (char)c );
            pos++;
        }
        // zprint(0 ,output, (char*)line_buffer);
    }
    return QString( QByteArray((const char*)line_buffer , pos) );
          
}
QStringList zmdump( unsigned char* data , int len )
{
    int i;
    QStringList slist ;
    
    slist.clear();
    
    for(i =0 ; i <= len ; i+=ucharS_IN_A_LINE )
    {
        slist.append (zldump( &data[i] , (ucharS_IN_A_LINE < (len - i)) ? ucharS_IN_A_LINE : len - i ) );
    }
    return slist ;
    
}

