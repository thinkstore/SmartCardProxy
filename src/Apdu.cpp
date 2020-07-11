#include "apdu.h"
//#include "conv.h"
#include "TString.h"
//"CLA=00,INS=A4,P1=04,P2=00,Lc=07,data=A0000000031010,Le=00"
// void get_param_value( char* param , TBuffer& value )
// {
//     char* p = 0 ;
//     int   len = 0 ;
    
//     p = strchr(param,'=');
//     if( p > 0 )
//     {
//         len = strlen( p + 1 );
//         value = TBuffer( (unsigned char*)p + 1 , len );
//     }
// }

// short Apdu::parse_command_string(char* command  )
// {
//     char*          sep ;
//     short          err = 0 ;
//     char*          p = 0;

//     TBuffer        cla ;
//     TBuffer        ins ;
//     TBuffer        p1 ;
//     TBuffer        p2 ;
//     TBuffer        lc ;
//     TBuffer        le ;
//     TBuffer        data ;

    
//     sep = strtok( command , ",");
//     while( sep )
//     {
//         p = 0 ;
//         if( !strncmp( sep , "CLA" , 3 ))
//         {
//             get_param_value( sep , cla );
//         }
//         else if( !strncmp( sep , "INS" , 3 ))
//         {
//             get_param_value( sep , ins );
//         }
//         else if( !strncmp( sep , "P1" , 2 ))
//         {
//             get_param_value( sep , p1 );
//         }
//         else if( !strncmp( sep , "P2" , 2 ))
//         {
//             get_param_value( sep , p2 );
//         }
//         else if( !strncmp( sep , "data" , 2 ))
//         {
//             get_param_value( sep , data );
//         }
//         else if( !strncmp( sep , "Le" , 2 ))
//         {
//             get_param_value( sep , le );
//         }
//         else if( !strncmp( sep , "Lc" , 2 ))
//         {
//             get_param_value( sep , lc );
//         }
//         sep = strtok(NULL ,",");
//     }
//     //TYPE 4 (CLA , INS , P1 , P2 , Lc , data , Le)
//     _command = cla + ins + p1 + p2 + lc + data + le ;
//     return err;
    
// }

// Apdu::Apdu( char* str )
// {
//     parse_command_string( str );
// }

// Apdu::Apdu( unsigned char* data, unsigned char data_len)
// {
//     _command = TBuffer( data , data_len );
// }

Apdu::Apdu( TBuffer& buffer )
{
    _sw = buffer.last(2);
    if( buffer.len() > 2 )
    {
        _data = buffer.first( buffer.len() - 2 );
    }
    _direction = FROM_CARD ;
}


TBuffer  Apdu::array()
{
    unsigned char lc = _data.len() ;
//    unsigned char le = 0;
    if( _direction == TO_CARD )
    {
        if( _data.len() > 0 )
        {
            return _command + TBuffer( &lc , 1 ) + _data ;
        }
        else 
        {
            return _command ;// + TBuffer( &le , 1 ) 
        }
    }
    else 
    {
        return _command + _data + _sw ;
    }
    
}
Apdu::Apdu(void)
{
}

Apdu::Apdu( uchar CLA ,uchar INS ,uchar P1,uchar P2, uchar Le )
{
    unsigned char cmd[10] ;
    unsigned char pos = 0 ;
    cmd[pos++] = CLA;
    cmd[pos++] = INS;
    cmd[pos++] = P1;
    cmd[pos++] = P2;

//    if( Le ) 
    {
        cmd[pos++] = Le ;
    }

    _command    = TBuffer( cmd , pos );
    _direction  = TO_CARD;

}

Apdu::Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,TBuffer& data)
{
    unsigned char cmd[4] ;
    cmd[0] = CLA;
    cmd[1] = INS;
    cmd[2] = P1;
    cmd[3] = P2;
    _command    = TBuffer( cmd , 4 );
    _data       = data ;
    _direction  = TO_CARD;
    
}

// Apdu::Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,TBuffer& data , unsigned char Le)
// {
//     _command = TBuffer(5);
//     _command[0] = CLA;
//     _command[1] = INS;
//     _command[2] = P1;
//     _command[3] = P2;
//     _command[4] = data.len();

//     _command   += data ;
//     _command   += TBuffer(&Le , 1 );
// }

uchar Apdu::sw1(void)
{
     // return _command[-2];
    return _sw[0];
}
uchar Apdu::sw2(void)
{
     // return _command[-1];
     return _sw[1];
}

// unsigned char* Apdu::data(void)
// {
//     return _command.head();
// }
// unsigned char* Apdu::command(void)
// {
//     return _command.head();
// }

unsigned short Apdu::len(void)
{
    return array().len() ;
}


TString  Apdu::name(void)
{
    if( _command.first(4) == TBuffer((unsigned char*)"\x00\xA4\x04\x00", 4))
    {
        return TString("SELECT");
    }
    else if( _command.first(2) == TBuffer((unsigned char*)"\x00\xB2",2)  )
    {
        return TString("READ RECORD");
    }
    else if(  _command.first(2) == TBuffer((unsigned char*)"\x80\xCA",2))
    {
        return TString("GET DATA");
    }
    else if( _command.first(4) == TBuffer((unsigned char*)"\x00\xC0\x00\x00",4))
    {
        return TString("GET RESPONSE");
    }
    else if( _command.first(4) == TBuffer((unsigned char*)"\x00\x84\x00\x00",4) )
    {
        return TString("GET CHALLENGE");
    }
    else if( _command.first(4) == TBuffer((unsigned char*)"\x80\xA8\x00\x00",4) )
    {
        return TString("GET PROC OPTIONS");
    }
    else if( _command.first(3) == TBuffer((unsigned char*)"\x00\x20\x00",3 ) )
    {
        return TString("VERIFY");
    }
    else if( _command.first(2) == TBuffer((unsigned char*)"\x80\xAE",2) )
    {
        return TString("GENERATE AC");
    }
    else if( _command.first(2) == TBuffer((unsigned char*)"\x00\x88",2 ) )
    {
        return TString("INTERNAL AUTHENTICATE");
    }    
    return TString();
    
}
Apdu& Apdu::operator=(const Apdu& b)
{
    if ( this != &b )
    {
        _command   = b.command();
        _data      = b.data();
        _sw        = b.sw();
        _direction = b.direction();
    }

    return *this;
}
Apdu::Apdu( const Apdu& a)
{
    this->_command   = a.command();
    this->_data      = a.data();
    this->_direction = a.direction();
    this->_sw        = a.sw();
}
