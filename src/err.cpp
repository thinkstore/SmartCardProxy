#include "err.h"

st_error err_msg[] =
{
    {
        ERROR_INPUT_CANCELED,
        0,
        "INPUT PROCESS CANCELED BY USER",
        0
    },
    {
        ERROR_HOST_CONNECTION,
        0,
        "HOST BAGLANTISI KURULAMADI",
        0
    },
    {
        ERROR_HOST_TO,
        0,
        "HOSTTAN CEVAP YOK",
        "HOST BAGLANTISINI KONTROL EDIN",
        0
    },

    {
        ERROR_CA_KEY_NOT_FOUND,
        0,
        "CA PUBLIC KEY BULUNAMADI",
        0,
        0
    },
    {
        ERROR_FORMAT,
        0,
        "VERI FORMATI HATALI",
        0,
        0
    },
    {
        ERROR_AFL_OUT_OF_RANGE,
        0,
        "AFL RANGE DISINDA ",
        0,
        0,
    },
    {
        ERROR_MISSING_MANDATORY_DATA,
        0,
        "ZORUNLU DATA EKSIKLIGI",
        0,
        0,
    },
    {
        ERROR_SDA_FAILED,
        0,
        "SDA BASARISIZ",
        0,
        0,
    },
    {
        ERROR_ISS_CERT_NOT_VALID,
        0,
        "ISSUER SERTIFIKASI HATALI",
        0,
        0,
    },
    {
        ERROR_PIN_INCORRECT,
        0,
        "HATALI SIFRE",
        0,
        0,
    },
    {
        ERROR_UNSUPPORTED_CVM,
        0,
        "CVM DESTEKLENMIYOR",
        0,
        0,
    },
    {
        ERROR_PIN_TRY_LIMIT_EXCEEDED,
        0,
        "PIN DENEME SAYISI ASILDI",
        0,
        0,
    },
    {
        ERROR_PIN_ENTRY_CANCELED,
        0,
        "PIN GIRISI BYPASS EDILDI",
        0,
        0,
    },
    {
        ERROR_CVM_FAILED,
        0,
        "CVM BASARISIZ",
        0,
        0,
    },
    {
        ERROR_INCORRECT_TERMINAL_PARAMETER,
        0,
        "HATALI TERMINAL PARAMETRESI",
        0,
        0,
    },
    {
        ERROR_INCORRECT_ACTION_CODE,
        0,
        "AKSIYON KODU HATALI",
        0,
        0,
    },
    {
        ERROR_DDA_FAILED,
        0,
        "DDA BASARISIZ",
        0,
        0,
    },
    {
        ERROR_COMMAND_NOT_ALLOWED,
        0,
        "SMART KART",
        "KOMUTUNUN CALISMASINA IZIN YOK",
        0,
    },
    {
        ERROR_SMC_CMD_FAILED,
        0,
        "SMART KART KOMUTU BASARISIZ OLDU",
        0,
        0,
    },
    {
        ERROR_READER_NOT_FOUND,
        0,
        "HERHANGI BIR",
        "SMART KART OKUYUCU",
        "BULUNAMADI",
    },
    {
        ERROR_READER_CONTEXT_ERROR,
        0,
        "OKUYUCU CONTEXT",
        "HATASI",
        0,
    },
    {
        ERROR_READER_CONNECT_ERROR,
        0,
        "OKUYUCU BAGLANTISI BASARISIZ",
        0,
        0,
    },
    {
        ERROR_CARD_NOT_PRESENT,
        0,
        "OKUYUDA KART YOK",
        0,
        0,
    },
    {
        ERROR_SMC_CONNECT_ERROR,
        0,
        "OKUYUDA KART YOK",
        0,
        0,
    },
    
};


short fill_err_msg(short err , st_error* e)
{
    int i ;
    for( i = 0 ; i < sizeof( err_msg )/sizeof(st_error) ; i++  )
    {
        if( err_msg[i].err == err )
        {
            *e = err_msg[i];
            return 0 ;
        }
    }
    return ERROR_UNKNOWN_ERROR ;
}
    
// short  handle_error( short err , wxTextCtrl* win )
// {
//     st_error detailed_err;
//     if(err == 0 ) return  err;
    
//     memset( &detailed_err , 0 , sizeof(st_error));
//     fill_err_msg( err , &detailed_err );
//     // if( detailed_err.line1 ) win->AppendText( wxString( detailed_err.line1) + "\n");
//     // if( detailed_err.line2 ) win->AppendText( wxString( detailed_err.line2) + "\n");
//     // if( detailed_err.line3 ) win->AppendText( wxString( detailed_err.line3) + "\n");

//     if( detailed_err.line1 ) win->AppendText( wxString::Format( "\n!!! %s !!!\n", detailed_err.line1) );
//     if( detailed_err.line2 ) win->AppendText( wxString::Format(   "!!! %s !!!\n", detailed_err.line2) );
//     if( detailed_err.line3 ) win->AppendText( wxString::Format(   "!!! %s !!!\n", detailed_err.line3) );

//     return err;
// }
