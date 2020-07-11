#ifndef __DEBUG_H__
#define __DEBUG_H__
#include "TBuffer.h"
#include <QString>
#include <QStringList>
#include <QPlainTextEdit>

void        zprint( unsigned short flags , FILE* output , char* base , ... );
void        ztrace( unsigned char cond   , FILE* output , char* descr , unsigned char* data , int len );
QString     zldump( unsigned char* line_addr , int len );
QStringList zmdump( unsigned char* data , int len );

#endif
