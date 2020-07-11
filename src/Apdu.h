#pragma once
/* #include "types.h" */
#include "TBuffer.h"

/** 
 * TYPE 0 (Lc , data )
 * Command transmitting data directly to the IC card, without any protocol.
 * Specific to T=1.
 */

/** 
 * TYPE 1 (CLA , INS , P1 , P2 )
 * Command to be executed without any data to pass to the IC card and without any
 * data expected from the card.
 */

/** 
 * TYPE 2 (CLA , INS , P1 , P2 , Le )
 * Command to be executed without any data to pass to the IC card, but expecting
 * some data from the IC card.
 */

/** 
 * TYPE 3 (CLA , INS , P1 , P2 , Lc , data )
 * Command to be executed without any data to pass to the IC card, but expecting
 * some data from the IC card.
 */

/** 
 * TYPE 4 (CLA , INS , P1 , P2 , Lc , data , Le)
 * Command to be executed without any data to pass to the IC card, but expecting
 * some data from the IC card.
 */

#define TO_CARD   1 
#define FROM_CARD 2 

class Apdu
{
  private:
    
    unsigned char   _direction;
    TBuffer _command;
    TBuffer _data;
    TBuffer _sw;
    
  public:

    Apdu(void);
    /* Apdu( unsigned char* data , unsigned char data_len ); */
    /* Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,unsigned char Le);  */
    /* Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,TBuffer& data); */
    /* Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,TBuffer& data , unsigned char Le); */
    Apdu( unsigned char CLA ,uchar INS ,uchar P1,uchar P2, uchar Le = 0 );
    Apdu( unsigned char CLA ,unsigned char INS ,unsigned char P1,unsigned char P2,TBuffer& data);
    
        //copy constructor
    Apdu( const Apdu& buf);
    Apdu& operator=(const Apdu& b);
    
    Apdu( char* str );
    Apdu( TBuffer& buffer );
    
    unsigned char    sw1(void);
    unsigned char    sw2(void);
    unsigned short   len(void);

    TString  name(void);
    inline TBuffer  command() const  { return _command; }
    inline TBuffer  data() const  { return _data; }
    inline TBuffer  sw() const  { return _sw; }
    inline unsigned char    direction() const  { return _direction; }

    TBuffer  array();
    
    inline unsigned char  cla() const { return _command[0]; }
    inline unsigned char  ins() const { return _command[1]; }
    inline unsigned char  p1() const { return _command[2]; }
    inline unsigned char  p2() const { return _command[3]; }
    
    
};


