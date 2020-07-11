#ifndef __STRING_H__
#define __STRING_H__

#include "TBuffer.h"

class TString
{
  public:
        //constructor
    TString();
    TString(int len); //allocate zero buffer
    TString(const char* data );
    TString(char* data );
    TString(char* data , int len );
    /* TString(QString& s); */
    
        //copy constructor
    TString( const TString& buf);
    TString( const TBuffer& buf);
	
        //operators
    char&  operator[](int i) const;
    TString& operator+=(const TString& b);

    TString  operator+(const TString& b1 );
    TString& operator=(const TString& b);
    TString& operator=(const char* b);
    TString& operator+=(const TBuffer& b);
    TString  operator+(const TBuffer& b1 );
    TString  operator+(const char& c );
    TString& operator+=(const char& b);
    
    bool operator==(const TString& b);
    bool operator!=(const TString& b);
	
        //destructor
    ~TString();

        //methods
    char* head() const{return _data;};
    int   len() const {return _len; };
    char* data() const{return _data;};

    TString upper(void);
    TString lower(void);
    TString left(char c );
    void    fill( char c , int size );
    
     
  private:
        //properties
    char* _data;
    int   _len  ;
        
};
#endif
