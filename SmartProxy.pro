#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T14:33:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartProxy
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
LIBS += -lWinSCard

DEPENDPATH += src

INCLUDEPATH += ./QtWebSocket

SOURCES += QtWebsocket/functions.cpp \
        QtWebsocket/QTlsServer.cpp \
        QtWebsocket/QWsFrame.cpp \
        QtWebsocket/QWsHandshake.cpp \
        QtWebsocket/QWsServer.cpp \
        QtWebsocket/QWsSocket.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/tprintf.cpp \
    src/Server.cpp \
    src/rdr.cpp \
    src/Apdu.cpp \
    src/TBuffer.cpp \
    src/conv.cpp \
    src/TString.cpp \
    src/debug.cpp

HEADERS  += QtWebsocket/functions.h \
        QtWebsocket/QTlsServer.h \
        QtWebsocket/QWsFrame.h \
        QtWebsocket/QWsHandshake.h \
        QtWebsocket/QWsServer.h \
        QtWebsocket/QWsSocket.h \
        QtWebsocket/WsEnums.h \
        src/mainwindow.h \
        src/tprintf.h \
    src/Server.h \
    src/rdr.h \
    src/Apdu.h \
    src/TBuffer.h \
    src/conv.h \
    src/TString.h \
    src/debug.h

FORMS    += mainwindow.ui
