#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SmartProxy");
    this->createStatusBar();
    this->serverToggle(true);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createStatusBar()
{
        // QStatusBar *statusBar = statusBar();

    QLabel*             error  ;
    error  = new QLabel( tr("  OK  ") );



    QLabel *name   = new QLabel( tr("  cihangirzengin@gmail.com  ") );

    QLabel*             reader_status_info ;
    reader_status_info = new QLabel( tr("NOT CONNECTED") );    

    reader_status_info->setToolTip( tr("Status of smart card reader.") );

    statusBar()->addWidget( error , 1 );
    statusBar()->addWidget( reader_status_info  );
    statusBar()->addWidget( name  );
}

void MainWindow::serverToggle(bool state){

    if(state){
        this->ui->startButton->setText("Stop Server");
        myServer = new Server(8080, QtWebsocket::Tcp);
    }
    else{
        this->ui->startButton->setText("Start Server");
        myServer->deleteLater();
    }
    
    
}
