#include "stdio.h"
#include "stdarg.h"
#include "tprintf.h"
unsigned long  std_out = (unsigned long)stdout;

#define MAX_MSG_LEN 1024

void tprintf(const char *format, ...) 
{
  va_list args;                  //variable args
  static char msg[MAX_MSG_LEN + 1];

  va_start(args, format);  
  vsprintf_s(msg, format, args);
  va_end(args);

  // fprintf (stdout, "%s\n", msg);
  fprintf ((FILE*)std_out, "%s\n", msg);

}

