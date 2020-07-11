#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <string.h>
#include <QString>
/* typedef unsigned char  uchar; */
/* typedef unsigned long  unsigned long; */
/* typedef unsigned short unsigned short; */
/* typedef unsigned char  unsigned char ; */
/* typedef short          short ; */

/* #define unsigned long unsigned long */
/* #define short  short */
/* #define unt16  unsigned short  */
/* #define unsigned char  unsigned char */
/* #define uchar   unsigned char  */

#ifndef MIN
#define MIN(x,y)  ( ((x) < (y)) ? (x) : (y) )
#endif

#ifndef MAX
#define MAX(x,y)  ( ((x) > (y)) ? (x) : (y) )
#endif

#define CLRBIT( STR, IDX ) ( (STR)[(IDX)/8] &= ~(0x01 << (7 - ((IDX)%8))) )
#define SETBIT( STR, IDX ) ( (STR)[(IDX)/8] |= (0x01 << (7 - ((IDX)%8))) )
#define GETBIT( STR, IDX ) (( ((STR)[(IDX)/8]) >> (7 - ((IDX)%8)) ) & 0x01)


class TString;
class TBuffer
{
public:
     //constructor
     TBuffer();
     TBuffer(int len); //allocate zero buffer
     TBuffer(unsigned char* data , int len);
     TBuffer(unsigned char b , int len ); 
     TBuffer(TString& str ); 
     TBuffer(QString str ); 
     TBuffer( const char* str );
     
     //copy constructor
     TBuffer( const TBuffer& buf);

     //operators
     uchar&  operator[](int i) const;
     TBuffer& operator+=(const TBuffer& b);

     TBuffer  operator+(const TBuffer& b1 );
     TBuffer& operator=(const TBuffer& b);

     bool operator==(const TBuffer& b);
     bool operator!=(const TBuffer& b);
     bool operator==(const unsigned short val);

     TString  ascii(void);
     TString  ascii( int start , int count );
     
     TBuffer  last( int count );
     TBuffer  range( int start , int count );
     TBuffer  first( int count );
     TString  string( int start , int count );
     TString  string();
     TString  toHexString( int start , int count );
     TString  toHexString();
     
     //destructor
     ~TBuffer();

     //methods
     uchar* head() const{return _data;};
     int   len() const {return _len; };
     uchar* data() const{return _data;};
     
private:
     //properties
     uchar* _data;
     int   _len  ;
        
};
#endif
