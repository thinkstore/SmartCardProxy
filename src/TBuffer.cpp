
#include "TBuffer.h"
#include "conv.h"
#include "TString.h"
#include "ctype.h"
#include "string.h"
#include "stdio.h"

TBuffer::TBuffer()
{
    _data =0;
    _len  =0;
}

TBuffer::TBuffer(int len)
    :_len(len)
{
    _data = 0;
    _data = new uchar [len];
    if( _data )
    {
        _len = len ;
        memset( _data , 0 , _len );
    }
    
}

TBuffer::TBuffer(unsigned char b , int len )
{
    _data = new unsigned char [len];
    memset( _data , b , len );
}

TBuffer::TBuffer( const TBuffer& buf):
    _data(0),
    _len(0)
{
    _data = new uchar [buf.len()];
    for(int i =0 ; i < buf.len() ; i++ )
        _data[i] = buf[i];

    _len = buf.len();
}

TBuffer::TBuffer(uchar* data , int len)
    :// _len(len),
    _data(0)
{
    _len = len ;
    _data = new uchar [len];
    for(int i=0 ; i < len ; i++)
        _data[i] = data[i];
}

TBuffer::TBuffer( const char* str )
{
    _len = strlen(str) ;
    _data = new uchar [_len];

    for(int i=0 ; i < _len ; i++)
        _data[i] = str[i];

}
TBuffer::TBuffer(TString& str )
{
    if( str.len() > 0 )
    {
        _data = new unsigned char [ str.len() / 2 ];
        str2hex(_data , str.data() );
        _len = str.len() / 2 ;
    }
    else 
    {
        _data = 0 ;
        _len  = 0 ;
    }
    
}

TBuffer::TBuffer(QString str )
{
    if( str.length() > 0 )
    {
        _data = new unsigned char [ str.length() / 2 ];
        str2hex(_data , str.toLatin1().data() );
        _len = str.length() / 2 ;
    }
    else 
    {
        _data = 0 ;
        _len  = 0 ;
    }
    
}



TBuffer::~TBuffer()
{
    if(_data) delete []_data;
}

uchar& TBuffer::operator[](int i) const 
{
    if ( i < 0 )
    {
        return _data[_len+i];
    }
    else
    {
        return _data[i];
    }
}

TBuffer& TBuffer::operator+=(const TBuffer& b)
{
    int i,j;
     
    if ( this != &b )
    {
        uchar* new_data = new uchar [_len + b.len() ];
        for(i=0; i < _len ; i++ )
            new_data[i] = _data[i];
		
        for(j=0; i < _len + b.len() ; i++ ,j++)
            new_data[i] = b[j];

        if(_data) delete []_data;

        _data = new_data;
        _len += b.len();

    }
    return *this;
}
TBuffer  TBuffer::operator+(const TBuffer& b1 )
{
    TBuffer b = *this;
    b += b1;
    return b;
}

TBuffer& TBuffer::operator=(const TBuffer& b)
{
    if ( this != &b )
    {
        uchar* new_data = new uchar [ b.len() ];

        for(int i=0; i < b.len() ; i++ )
            new_data[i] = b[i];

        if(_data) delete []_data;

        _data = new_data;
        _len  = b.len();
    }
    return *this;
}

bool TBuffer::operator==(const TBuffer& b)
{
     if( this == &b )
          return true;
     
     if ( this != &b )
     {
          if( this->_len != b.len() )
               return false;
          if( memcmp( this->_data , b.head() , this->_len ))
               return false ;
     }
     return true;     
}

bool TBuffer::operator!=(const TBuffer& b)
{
     if( this == &b )
          return false;
     
     if ( this != &b )
     {
          if( this->_len != b.len() )
               return true;
          if( memcmp( this->_data , b.head() , this->_len ))
               return true ;
     }
     return false;     
}

bool TBuffer::operator==(const unsigned short val)
{
     unsigned short tmp=0;
     
     for(int i = 0 ; i < _len ; i++ )
          tmp += _data[i] << (8*(_len-i-1));
     
     return (tmp==val);

}

TString TBuffer::ascii(void)
{
    char c;
    TString str(this->len()+1);
    
    for(int i=0 ; i < _len ; i++ )
    {
        c = _data[i] & 0x7f ;
        sprintf( &str[i] , "%c" , (isprint(c)) ? _data[i] : '.' );
    }
    return str;
}

TBuffer  TBuffer::first(int count)
{
    TBuffer tmp(count);
    memcpy( tmp.head() , _data , count );
    return tmp;
}
TBuffer  TBuffer::range(int start , int count)
{
    // TBuffer tmp(count);

    if( start < 0 )
        start = _len + start;
     
    if(start+count > _len )
        count = _len - start ;
    // memcpy( tmp.head() , _data+start , count );
    // return tmp;
    return TBuffer( _data + start , count );
    
}
TBuffer  TBuffer::last(int count)
{
    TBuffer tmp(count);
    memcpy( tmp.head() , _data + _len - count   , count );
    return tmp;
}


TString TBuffer::string( int start , int count )
{
    int i;
    int  pos=0;
    char    tmp[3+1];
    TString str;

    if(count > 0 )
    {
        for(i=start ; i < (start + count) && (i < _len)  ; i++ )
        {
            sprintf( tmp ,  "%02X " , _data[i] & 0xFF  );
            str += TString( tmp );
            pos += 3;
        }
    }

    if( str[-1] == ' ' ){
        str = TString( str.data() , str.len() - 1 );
    }

    
    return str;
    
}


TString TBuffer::toHexString( int start , int count )
{
    int i;
    int  pos=0;
    char    tmp[3+1];
    TString str;

    if(count > 0 )
    {
        for(i=start ; i < (start + count) && (i < _len)  ; i++ )
        {
            sprintf( tmp ,  "%02X" , _data[i] & 0xFF  );
            str += TString( tmp );
            pos += 3;
        }
    }

    return str;
}

TString TBuffer::toHexString()
{
    return toHexString(0,_len);
}



TString TBuffer::string()
{
    return string(0 , _len );
}


TString  TBuffer::ascii( int start , int count )
{
    char c;
    TString str;
    
    for(int i=start ; (i < _len) && i < (start + count) ; i++ )
    {
        // c = _data[i] & 0x7f ;
        c = (isprint(_data[i] & 0x7f)) ? _data[i] : '.' ;
        str += c;
        // sprintf( &str[i] , "%c" , (isprint(c)) ? _data[i] : '.' );
    }
    return str;
}
