#ifndef __ERR_H__
#define __ERR_H__

#include "TBuffer.h"

typedef struct
{
    short  err;
    unsigned char  flags;
    const  char* line1;
    const  char* line2;
    const  char* line3;
}st_error;

short fill_err_msg(short err , st_error* e);
/* short  handle_error( short err , wxTextCtrl* win ); */

#define ERROR_START                        100
#define ERROR_FORMAT                       1 + ERROR_START 
#define ERROR_AFL_OUT_OF_RANGE             2 + ERROR_START 
#define ERROR_AFL_INCORRECT                3 + ERROR_START 
#define ERROR_MISSING_MANDATORY_DATA       4 + ERROR_START 
#define ERROR_SDA_FAILED                   5 + ERROR_START 
#define ERROR_ISS_CERT_NOT_VALID           6 + ERROR_START 
#define ERROR_PIN_VERIFIED                 7 + ERROR_START 
#define ERROR_PIN_INCORRECT                9 + ERROR_START 
#define ERROR_UNSUPPORTED_CVM              10 + ERROR_START 
#define ERROR_PIN_TRY_LIMIT_EXCEEDED       11 + ERROR_START 
#define ERROR_PIN_ENTRY_CANCELED           12 + ERROR_START 
#define ERROR_CVM_FAILED                   13 + ERROR_START 
#define ERROR_SUPPORTED_CVM                14 + ERROR_START 
#define ERROR_INCORRECT_TERMINAL_PARAMETER 15 + ERROR_START
#define ERROR_INCORRECT_ACTION_CODE        16 + ERROR_START 
#define ERROR_DDA_FAILED                   17 + ERROR_START 
#define ERROR_COMMAND_NOT_ALLOWED          18 + ERROR_START 
#define ERROR_SMC_CMD_FAILED               19 + ERROR_START 
#define ERROR_UNKNOWN_ERROR                20 + ERROR_START 
#define ERROR_COM                          21 + ERROR_START 
#define ERROR_SOCKET                       22 + ERROR_START 
#define ERROR_INPUT_CANCELED               23 + ERROR_START 
#define ERROR_EXPIRED_CERTIFICATE          24 + ERROR_START 
#define ERROR_ICC_DATA_MISSING             25 + ERROR_START 
#define ERROR_WRONG_CERTIFICATE            26 + ERROR_START 
#define ERROR_CHECKSUM                     27 + ERROR_START 
#define ERROR_SDA_TAGLIST                  28 + ERROR_START 
#define ERROR_CA_KEY_NOT_FOUND             29 + ERROR_START 
#define ERROR_READER_NOT_FOUND             30 + ERROR_START 
#define ERROR_READER_CONTEXT_ERROR         31 + ERROR_START 
#define ERROR_READER_CONNECT_ERROR         32 + ERROR_START 
#define ERROR_CARD_NOT_PRESENT             33 + ERROR_START 
#define ERROR_CONTEXT_RELEASE_ERROR        34 + ERROR_START 
#define ERROR_READER_DISCONNECT_ERROR      34 + ERROR_START 
#define ERROR_SMC_CONNECT_ERROR            35 + ERROR_START 
#define ERROR_SERVICE_NOT_ALLOWED          36 + ERROR_START 
#define ERROR_OFFLINE_PIN_INCORRECT        37 + ERROR_START 
#define ERROR_HOST_TO                      38 + ERROR_START 
#define ERROR_HOST_CONNECTION              39 + ERROR_START 

#endif
