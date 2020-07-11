//#include "util.h"
#include "rdr.h"
#include <winerror.h>
//#include "debug.h"
#include "TString.h"
//#include "MainPanel.h"
#include "tprintf.h"

// SCARDHANDLE    scard_handle;
// unsigned long         protocol = 0 ;

Rdr::Rdr(QObject* parent)
    :QObject(parent),
     protocol(0),
     scard_handle(0),
     scard_context(0)
         // lo_level_model(0)
{
    readers.clear();
    status = READER_STATUS_NOT_CONNECTED;
    this->protocol = 0 ;
        // init_models();
    list_readers();
}

// void Rdr::init_models(void)
// {
//     QStringList headerLabels;
//     headerLabels << tr("HEX") << tr("ASCII") ;
//     if( lo_level_model == 0 )
//     {
//         lo_level_model = new StandardTreeModel(this);
//     }
//     lo_level_model->clear();
//     lo_level_model->setColumnCount( 2 );
//     lo_level_model->setHorizontalHeaderLabels( headerLabels );

// }
Rdr::~Rdr()
{
    disconnect();

}

QString Rdr::getReaderList(void){

    QString readersAsStr ;
    int     numOfReaders = 0 ;

    if( !this->list_readers() ){
        readersAsStr = "[\"";
        numOfReaders = this->readers.size();
        for(int counter = 0 ; counter < numOfReaders ; counter ++ ){
            readersAsStr += this->readers.at(counter) ;
            if( counter != (numOfReaders - 1) ){
                readersAsStr +=  ",";
            }
        }
        readersAsStr += "\"]";
    }

    return readersAsStr;
    
}

short Rdr::list_readers()
{
        // unsigned short          pos = 0 ;
    short           err = 0 ;
    LPTSTR          pmszReaders = NULL;
    LPTSTR          pReader;
    LONG            lReturn;
    DWORD           cch = SCARD_AUTOALLOCATE;

    do 
    {
        err = ERROR_READER_NOT_FOUND;
        lReturn = SCardListReaders(scard_context, NULL, (LPTSTR)&pmszReaders, &cch );
        if( lReturn != SCARD_S_SUCCESS ) break;
         
        readers.clear();
        
        pReader = pmszReaders;
        while ( '\0' != *pReader )
        {
                // Display the value.
                // Advance to the next value.
                //readers.append(pReader) ;
            readers << QString::fromWCharArray(pReader);
            pReader += wcslen(pReader) + 1;


        }

        SCardFreeMemory( scard_context ,pmszReaders );
        err = 0 ;
        
    }while(0);
     
    emit reader_error(err);
    
    return err;
}
short Rdr::connect( QString candidate_reader )
{
    short           err = 0;
    unsigned long   cuchar = 32;
    DWORD    dwAP;
    wchar_t            arrsReaderName[85] ;
    unsigned long   cch = 200;
    uchar            bAttr[32];
    unsigned long   dwState;
    int             prevStatus = 0 ;
    
    do
    {

        if(status == READER_STATUS_CONNECTED )
            break;

        prevStatus = status ;
        
        if(SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL,&scard_context )!= SCARD_S_SUCCESS )
        {
            err = ERROR_READER_CONTEXT_ERROR;
            break;
        }

        if(SCardConnect(scard_context,  candidate_reader.toStdWString().c_str()
                        ,SCARD_SHARE_EXCLUSIVE
                        ,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1
                        ,&scard_handle ,
                        &dwAP )!= SCARD_S_SUCCESS)
        {
            err = ERROR_READER_CONNECT_ERROR;
            break;
        }
        
        if(SCardStatus(scard_handle,arrsReaderName,&cch,&dwState,&protocol,(LPBYTE)&bAttr,&cuchar) != SCARD_S_SUCCESS )
        {
            err = ERROR_CARD_NOT_PRESENT;
            break;
        }
        
        current_reader  = candidate_reader ;
        status          = READER_STATUS_CONNECTED;

        if( prevStatus != status )
            emit statusChanged(status);        

        
    }while(0);
    emit reader_error(err);

    return err;

}

short Rdr::disconnect(void)
{
    short err= 0 ;
    int   prevStatus = this->status ;
    
    do 
    {
        if( scard_handle == 0 ) break;
        if( status == READER_STATUS_NOT_CONNECTED ) break;

        if( SCardDisconnect( scard_handle, SCARD_UNPOWER_CARD) != SCARD_S_SUCCESS )
        {
            err = ERROR_READER_DISCONNECT_ERROR;
            break;
        }
        
        if( SCardReleaseContext(scard_context) != SCARD_S_SUCCESS ) 
        {
            err = ERROR_CONTEXT_RELEASE_ERROR;
            break;
        }

        status          = READER_STATUS_NOT_CONNECTED;

    }while(0);
    emit reader_error(err);

    if( prevStatus != this->status )
    {
        emit statusChanged( this->status );
    }
    
    return err;
}

short Rdr::talk(Apdu& send , Apdu& rcvd )
{
    short  err = 0 ;
    unsigned char  rcvd_data[512] ;
    unsigned long rcvd_len = sizeof(rcvd_data) ;

    do
    {
        memset( rcvd_data , 0 , sizeof(rcvd_data));

        TBuffer send_command = send.array();

        if( protocol == SCARD_PROTOCOL_T0 )
        {
                // err = SCardTransmit(scard_handle, SCARD_PCI_T0, send.data() , send.len() , NULL, rcvd_data , &rcvd_len );
            err = SCardTransmit(scard_handle, SCARD_PCI_T0, send_command.data() , send_command.len() , NULL, rcvd_data , &rcvd_len );
        }
        else if( protocol == SCARD_PROTOCOL_T1 )
        {
                // err = SCardTransmit(scard_handle, SCARD_PCI_T1, send.data(), send.len() , NULL , rcvd_data , &rcvd_len );
            err = SCardTransmit(scard_handle, SCARD_PCI_T1, send_command.data(), send_command.len() , NULL , rcvd_data , &rcvd_len );
        }

        if(err) break;
        
        TBuffer cmd = TBuffer(rcvd_data , rcvd_len );
        rcvd = Apdu( cmd );
        
        emit trace( send , rcvd );
        QCoreApplication::processEvents();

            // tprintf("send : %s" , TString(send_command).data() );
            // tprintf("rcvd : %s" , TString(TBuffer(rcvd_data , rcvd_len )).data() );

        switch( err )
        {
            case SCARD_W_REMOVED_CARD:
                break;
            case SCARD_W_RESET_CARD:
                break;
            case SCARD_W_UNPOWERED_CARD:
                break;
            case SCARD_W_UNRESPONSIVE_CARD:
                break;
            case SCARD_W_UNSUPPORTED_CARD:
                break;
            case SCARD_E_SERVICE_STOPPED:
                break;
            case SCARD_E_NO_SERVICE:
                break;
            case SCARD_E_CARD_UNSUPPORTED:
                break;
            case SCARD_E_DUPLICATE_READER:
                break;
            case SCARD_E_READER_UNSUPPORTED:
                break;
            case SCARD_E_PCI_TOO_SMALL:
                break;
            case SCARD_P_SHUTDOWN:
                break;
            case SCARD_E_READER_UNAVAILABLE:
                break;
            case SCARD_E_NOT_TRANSACTED:
                break;
            case SCARD_E_INVALID_ATR:
                break;
            case SCARD_F_UNKNOWN_ERROR:
                break;
            case SCARD_F_COMM_ERROR:
                break;
            case SCARD_E_SYSTEM_CANCELLED:
                break;
            case SCARD_E_INVALID_VALUE:
                break;
            case SCARD_E_NOT_READY:
                break;
            case SCARD_E_PROTO_MISMATCH:
                break;
            case SCARD_E_CANT_DISPOSE:
                break;
            case SCARD_E_UNKNOWN_CARD:
                break;
            case SCARD_E_NO_SMARTCARD:
                break;
            case SCARD_E_SHARING_VIOLATION:
                break;
            case SCARD_E_TIMEOUT:
                break;
            case SCARD_E_UNKNOWN_READER:
                break;
            case SCARD_E_INSUFFICIENT_BUFFER:
                break;
            case SCARD_F_WAITED_TOO_LONG:
                break;
            case SCARD_E_NO_MEMORY:
                break;
            case SCARD_E_INVALID_TARGET:
                break;
            case SCARD_E_INVALID_PARAMETER:
                break;
            case SCARD_E_INVALID_HANDLE:
                break;
            case SCARD_E_CANCELLED:
                break;
            case SCARD_F_INTERNAL_ERROR:
                break;
                  
        }
        if(err) break;

        if( rcvd.sw1()==0x61 )
        {
            Apdu send(0x00, 0xC0 , 0x00, 0x00 , rcvd.sw2());
            err = talk( send , rcvd );
        }
        else if( rcvd.sw1()==0x6C )
        {
            send = Apdu( send.cla() , send.ins() , send.p1() , send.p2() , rcvd.sw2() );
            err = talk( send , rcvd );
        }

        if( rcvd.sw1() != 0x90 && rcvd.sw2() != 0x00)
            err = ERROR_SMC_CMD_FAILED;

    }while(0);

    emit reader_error(err);
    return err;
    
}

short Rdr::cold_reset(unsigned char* atr , unsigned short* len )
{

    short           err = 0 ;
    wchar_t         arrsReaderName[85] ;
    unsigned long   cuchar = 32;
        // unsigned long   dwAP=0;
    unsigned long   cch = 200;
    uchar            bAttr[32];
    unsigned long   dwState;

    do 
    {

        if( scard_handle == 0 )                      break;
        if( status == READER_STATUS_NOT_CONNECTED  ) break;
        

        if( SCardReconnect(scard_handle,SCARD_SHARE_EXCLUSIVE,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,SCARD_UNPOWER_CARD,&protocol ) != SCARD_S_SUCCESS)
        {
            err = ERROR_READER_CONNECT_ERROR;
            break;
        }
        

        if( SCardStatus(scard_handle,
                        arrsReaderName,
                        &cch,
                        &dwState,
                        &protocol,
                        (LPBYTE)&bAttr,
                        &cuchar)!= SCARD_S_SUCCESS)
        {
            err = ERROR_CARD_NOT_PRESENT;
            break;
        }
        
        *len = cuchar;
        memcpy( atr , bAttr , *len );


            //emit trace( tr("PC ----> CARD") , tr("POWER ON\n") , tr("PC <---- CARD") , TBuffer( (unsigned char*)bAttr , cuchar) );

    }while(0);
    emit reader_error(err);
    
    return err;
}

// void Rdr::lo_level_trace( TBuffer& send , TBuffer& rcvd )
// {
    
//     QStringList slist;
//     QStandardItem* item = 0;
    
//     if( send.len() > 0 )
//     {
//         item = new QStandardItem( QIcon(":/pc.png") , "" );
//         lo_level_model->appendRow( item );
//         lo_level_model->appendBuffer( item , send );
//     }

//     if( rcvd.len() > 0 )
//     {
//         item = new QStandardItem( QIcon(":/chip.png") , "" );
//         lo_level_model->appendRow( item );
//         lo_level_model->appendBuffer( item , rcvd );
//     }
//     emit updateTreeView();
// }

// void Rdr::lo_level_trace( Apdu& send , Apdu& rcvd )
// {
//     QStringList slist;
//     QStandardItem* item = 0;
    
//     if( send.len() > 0 )
//     {
//         item = new QStandardItem( QIcon(":/pc.png") , send.name().data() );
//         lo_level_model->appendRow( item );
//         lo_level_model->appendBuffer( item , send.array() );
//         tprintf( "%s:%s", "SEND"  , TString(send.array()).data());
//     }

//     if( rcvd.len() > 0 )
//     {
//         item = new QStandardItem( QIcon(":/chip.png") , "" );
//         lo_level_model->appendRow( item );
//         lo_level_model->appendBuffer( item , rcvd.array() );
//         tprintf( "%s:%s", "RCVD" , TString(rcvd.array()).data());
//     }

//     emit updateTreeView();
// }


