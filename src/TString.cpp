
#include "TString.h"
#include "conv.h"
#include <ctype.h>

TString::TString()
{
     _data =0;
     _len  =0;
}

TString::TString(int len) //without ending null character
 :_len(len)
{
    _data = 0 ;
    _data = new char [len+1];

    if( _data !=0 )
    {
        memset( _data , 0 , len + 1 );
    }
}

TString::TString(char* data , int len )
{

    _data = 0 ;
    _data = new char [len+1];

    if( _data !=0 )
    {
        memset( _data , 0 , len + 1 );
        memcpy( _data , data , len );
        _len = len  ;
    }
}

// TString::TString(QString& s)
// {
//     _data = 0 ;
//     _data = new char [s.length()+1];

//     if( _data !=0 )
//     {
//         memset( _data , 0 , s.length() + 1 );
//         memcpy( _data , s.toAscii().data() , s.length() );
//         _len = s.length()  ;
//     }
// }

TString::TString( const TString& buf):
     _data(0),
     _len(0)
{
     _data = new char [buf.len()+1];

     if( _data != 0 )
     {
         memset( _data , 0 , buf.len()+1 );
         memcpy( _data , buf.data() , buf.len() );
         _len = buf.len();
     }
}

TString::TString( const TBuffer& buf)
{
    _data = 0 ;
    _data = new char[buf.len()*2 + 1];
    _len  = 0 ;
    
    if(_data )
    {
        memset( _data , 0 , buf.len()*2 + 1);
        for( int i = 0 ; i < buf.len() ; i++ )
        {
            _len += sprintf( &_data[_len] , "%02X" , buf[i] );
        }
    }
    

}



TString::TString(char* data )
 :// _len(len),
     _data(0)
{
    _len = strlen(data) ;
    if( _len > 0 )
    {
        _data = new char [_len+1];
        if( _data != 0  )
        {
            memset( _data , 0 , _len + 1 );
            memcpy( _data , data , _len );
        }
    }
}
TString::TString(const char* data )
    :// _len(len),
    _data(0)
{
    _len = strlen(data) ;
    if( _len > 0 )
    {
        _data = new char [_len+1];
        if( _data != 0  )
        {
            memset( _data , 0 , _len + 1 );
            memcpy( _data , data , _len );
        }
    }
}


TString::~TString()
{
     if(_data) delete []_data;
}

char& TString::operator[](int i) const 
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

TString& TString::operator+=(const TString& b)
{
    int i = 0 ,j = 0 ;

     if ( this != &b )
     {
         char* new_data = new char [_len + b.len() + 1 ]; ;

         for(i=0; i < _len ; i++ )
             new_data[i] = _data[i];

         for(j=0; i < _len + b.len() ; i++ ,j++)
             new_data[i] = b[j];

         new_data[i] = 0;
         
         if(_data) delete []_data;
         _data = new_data;
         _len += b.len();

         // prev_len = _len;
         // _len = _len + b.len();
         // new_data = new char [_len + 1 ];
         // if( new_data )
         // {
         //     memset( new_data , 0     , _len + 1 );
         //     memcpy( new_data , _data , _len );
         //     memcpy( &new_data[prev_len]  , b.data() , b.len() );
             
         //     if(_data) delete []_data;

         //     _data = new_data;
         // }
         
     }
     return *this;
}

TString& TString::operator+=(const char& b)
{
    _len++;

    char* new_data = 0 ;
    new_data = new char [_len + 1 ];
    if( new_data )
    {
        memset( new_data , 0 , _len + 1 );
        memcpy( new_data , _data , _len - 1);
        
        new_data[_len - 1 ] = b;

        if(_data) delete []_data;

        _data = new_data;
    }
    
    return *this;
}


TString  TString::operator+(const TString& b1 )
{
     TString b = *this;
     b += b1;
     return b;

}

TString& TString::operator+=(const TBuffer& b)
{
    int i;
     
    char* new_data = 0 ;
        
    new_data = new char [_len + b.len()*2 + 1];

    if( new_data != 0 )
    {
        memset( new_data , 0 , _len + b.len()*2 + 1);
        memcpy( new_data , _data , _len );
        for( i = 0 ; i < b.len() ; i++ )
        {
            _len += sprintf( &new_data[_len], "%02X" , b[i] );
        }
        
        if(_data) delete []_data;
        _data = new_data;

    }

    return *this;
}

TString  TString::operator+(const TBuffer& b1 )
{
    TString b = *this;
    b += b1;
    return b;
}
TString  TString::operator+(const char& c )
{
    char* new_data = 0 ;
    new_data = new char [_len + 1 + 1 ];
    if( new_data != 0 )
    {
        memset( new_data , 0 , _len + 1 + 1 );
        memcpy( new_data , _data , _len  );
        new_data[_len++] = c ;
        
        if(_data) delete []_data;
        _data = new_data;
    }
    
    return *this;
}


TString& TString::operator=(const TString& b)
{
    if ( this != &b )
    {
        char* new_data = 0 ;

        new_data = new char [ b.len() + 1 ];
        if( new_data )
        {
            memset( new_data , 0 , b.len() + 1);
            memcpy( new_data , b.data() , b.len() );
            
            if(_data) delete []_data;

            _data = new_data;
            _len  = b.len();
        }
    }
    return *this;
}

TString& TString::operator=(const char* b)
{
    int len = strlen(b);

    
    if ( this->_data != b )
    {
        char* new_data = 0 ;
        int   i =  0 ;
        
        new_data = new char [ len + 1 ];
        if( new_data != 0 )
        {
            for(i=0; i < len ; i++ )
                new_data[i] = b[i];
            
            new_data[i] = 0;
            
            if(_data) delete []_data;
            
            _data = new_data;
            _len  = len;
        }
    }
    return *this;
}



bool TString::operator==(const TString& b)
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

bool TString::operator!=(const TString& b)
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

TString TString::upper(void)
{
    TString u(this->_len) ;
    
    for( int i = 0 ; i < this->_len ; i++ )
    {
        u[i] = toupper(_data[i]);
    }

    return u;
    
}

TString TString::lower(void)
{
    TString u(this->_len) ;
    
    for( int i = 0 ; i < this->_len ; i++ )
    {
        u[i] = tolower(_data[i]);
    }

    return u;

}

TString TString::left(char c )
{
    char* ptr = strchr( this->_data , c );
    if( ptr == 0 ) return TString();
    
    return TString( _data , ptr - _data );
    
}

void TString::fill( char c , int size )
{
    int i = 0 ;
    char* new_data = 0 ;
    

    if( _len >= size ) return ;
    

    new_data = new char[size + 1];
    for( i = 0 ; i < _len ; i++ )
    {
        new_data[i] = _data[i];
    }
    
    for( ; i < _len + size ; i++ )
    {
        new_data[i]=c;
    }
    new_data[i] = 0 ;
    
    if(_data) delete []_data;
            
    _data = new_data;
    _len  = _len + size ;

    
}
