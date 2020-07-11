#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Server.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void serverToggle(bool);


private:
    Ui::MainWindow *ui;
    void createStatusBar();
    Server* myServer;



};

#endif // MAINWINDOW_H
