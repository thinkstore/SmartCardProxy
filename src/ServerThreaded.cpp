/*
Copyright 2013 Antoine Lafarge qtwebsocket@gmail.com

This file is part of QtWebsocket.

QtWebsocket is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

QtWebsocket is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with QtWebsocket.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ServerThreaded.h"
#include <iostream>

ServerThreaded::ServerThreaded()
{
	// int port = 9090;
	// server = new QtWebsocket::QWsServer(this);
	// if (! server->listen(QHostAddress::Any, port))
	// {
	// 	std::cout << QObject::tr("Error: Can't launch server").toStdString() << std::endl;
	// 	std::cout << QObject::tr("QWsServer error : %1").arg(server->errorString()).toStdString() << std::endl;
	// }
	// else
	// {
	// 	std::cout << QObject::tr("Server is listening port %1").arg(port).toStdString() << std::endl;
	// }
	// QObject::connect(server, SIGNAL(newConnection()), this, SLOT(processNewConnection()));
}

ServerThreaded::~ServerThreaded()
{
}

void ServerThreaded::run(int port){

    server = new QtWebsocket::QWsServer(this);
    if (! server->listen(QHostAddress::Any, port))
    {
        std::cout << QObject::tr("Error: Can't launch server").toStdString() << std::endl;
        std::cout << QObject::tr("QWsServer error : %1").arg(server->errorString()).toStdString() << std::endl;
    }
    else
    {
        std::cout << QObject::tr("Server is listening port %1").arg(port).toStdString() << std::endl;
    }
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(processNewConnection()));
}


void ServerThreaded::processNewConnection()
{
	std::cout << QObject::tr("Client connected").toStdString() << std::endl;

	// Get the connecting socket
	QtWebsocket::QWsSocket* socket = server->nextPendingConnection();

	// Create a new thread and giving to him the socket
	SocketThread* thread = new SocketThread(socket);
	
	// connect for message broadcast
	QObject::connect(socket, SIGNAL(frameReceived(QString)), this, SIGNAL(broadcastMessage(QString)));
	QObject::connect(this, SIGNAL(broadcastMessage(QString)), thread, SLOT(sendMessage(QString)));

	// Starting the thread
	thread->start();
}
