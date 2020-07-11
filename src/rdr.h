#pragma once
/* #include "std.h" */
#include "Apdu.h"
#include <winscard.h>
#include "TBuffer.h"
#include "err.h"
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QObject>
#include <QModelIndex>
#include <QCoreApplication>


#define READER_ACTION_CONNECT     1 
#define READER_ACTION_DISCONNECT  2 

#define READER_STATUS_CONNECTED       1 
#define READER_STATUS_NOT_CONNECTED   2 

/* extern SCARDCONTEXT   scard_context; */
/* extern SCARDHANDLE    scard_handle; */
/* extern unsigned long         protocol; */


typedef struct 
{
	unsigned char  CLA;
	unsigned char  INS;
	unsigned char  P1;
	unsigned char  P2;
	unsigned char  Le;
	unsigned char  Lc;
	unsigned char  data[255];
	unsigned char  len ;
	unsigned char  type;
}st_smc_command;

class Rdr : public QObject
{
	Q_OBJECT

  private:
	void init_models(void);
    
  public:
	explicit Rdr(QObject* parent=0);
	~Rdr();

  signals:
	void trace( Apdu& send , Apdu& rcvd );
	void trace( QString , QString , QString , TBuffer& rcvd );
	void reader_error(short err);
	    /* void updateTreeView(); */
	void statusChanged(int newStatus);
     
	public slots:
		short  list_readers(void);
		short  connect( QString candidate );
		short  disconnect( void );
		short  cold_reset(unsigned char* atr , unsigned short* len );
     
  public:
		unsigned long         protocol;
		SCARDHANDLE           scard_handle;
		SCARDCONTEXT          scard_context;

                            
		QStringList           readers;
		QString               current_reader;
		int                   status;

		short  talk(Apdu& send , Apdu& rcvd );
		QString getReaderList(void);

		    /* StandardTreeModel*    lo_level_model; */
		    /* void                  lo_level_trace( Apdu& send , Apdu& rcvd ); */
		    /* void                  lo_level_trace( TBuffer& send , TBuffer& rcvd ); */
     
};

