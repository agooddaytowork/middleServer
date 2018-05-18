#include "bridgeserver.h"
#define pollingInterval 200
bridgeServer::bridgeServer(const int &port, QObject *parent): QObject(parent), m_ServerPOrt(port), m_bridgeServer(new QTcpServer(this)), m_isBusy(false), m_TimeOutTimer(new QTimer(this))
{
    inputBuffer.clear();
    QObject::connect(m_bridgeServer,&QTcpServer::newConnection, this, &bridgeServer::newConnectionHandler);
    QObject::connect(this,SIGNAL(letWriteToUser(QByteArray)),this,SLOT(writeToUser(QByteArray)));

    m_TimeOutTimer->setInterval(pollingInterval);
    m_TimeOutTimer->setSingleShot(false);
    QObject::connect(m_TimeOutTimer,&QTimer::timeout,this,&bridgeServer::readyReadHandler);


}

void bridgeServer::start()
{
    if(m_bridgeServer->listen(QHostAddress(QHostAddress::Any),m_ServerPOrt))
    {
        qDebug() << "Server is listening on Port: " + QString::number(m_ServerPOrt);
        m_TimeOutTimer->start();
    }

}

void bridgeServer::newConnectionHandler()
{
    QTcpSocket* newClient = m_bridgeServer->nextPendingConnection();

    userList.append(newClient);

    qDebug() << "Server side: Client list count: " + QString::number(userList.count());


    in.setDevice(newClient);
    in.setVersion(QDataStream::Qt_5_8);

    connect(newClient, SIGNAL(readyRead()),this,SLOT(readyReadHandler()));
    connect(newClient,SIGNAL(disconnected()),this,SLOT(clientDiskConnectedHandler()));
    connect(newClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketErrorHandler(QAbstractSocket::SocketError)));

}

void bridgeServer::readyReadHandler()
{

    QTcpSocket* theTCPClient = dynamic_cast<QTcpSocket *> (sender());

    if(theTCPClient)
    {
        in.setDevice(theTCPClient);
    }

    in.startTransaction();

    QByteArray dataFromUser;

    in >> dataFromUser;

    if(!in.commitTransaction()) return;
    emit toFountainDevices(dataFromUser);

}

void bridgeServer::clientDiskConnectedHandler()
{
    if(auto client = dynamic_cast<QTcpSocket *>(sender()))
    {
       bool status = false;
        userList.removeOne(client);

        qDebug() << "Server Side remove disconnectedClient :" + status;
    }
}

void bridgeServer::socketErrorHandler(QAbstractSocket::SocketError err)
{
    qDebug() << "Error handler SERVER SIDE";

    auto client = dynamic_cast<QTcpSocket *>(sender());

    switch (err) {
    case QAbstractSocket::ConnectionRefusedError:

        if(client)
        {
            userList.removeAll(client);
        }

        qDebug() << "ConnectionRefusedError";
        break;

    case QAbstractSocket::RemoteHostClosedError:

        if(client)
        {
            userList.removeAll(client);
        }
         qDebug() << "RemoteHostClosedError";

        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "HostNotFoundError";

        break;
    case QAbstractSocket::SocketAccessError:
        qDebug() << "SocketAccessError";

        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() << "SocketTimeoutError";

        break;
    case QAbstractSocket::DatagramTooLargeError:
        qDebug() << "DatagramTooLargeError";

        break;
    case QAbstractSocket::NetworkError:
        qDebug() << "NetworkError";

        break;
    case QAbstractSocket::AddressInUseError:
        qDebug() << "AddressInUseError";

        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        qDebug() << "SocketAddressNotAvailableError";

        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        qDebug() << "UnsupportedSocketOperationError";

        break;
    case QAbstractSocket::TemporaryError:
        qDebug() << "TemporaryError";

        break;
    case QAbstractSocket::UnknownSocketError:
        qDebug() << "UnknownSocketError";

        break;

    default:
        break;
    }
}

void bridgeServer::fromFountainDevices(const QByteArray &data)
{
    if(userList.count()>0)
    {
        if(!m_isBusy )
        {
            emit letWriteToUser(data);
        }
        else
        {
            inputBuffer.append(data);
        }
    }

}

void bridgeServer::writeToUser(const QByteArray &data)
{

    m_isBusy = true;
    foreach (QTcpSocket* theClient, userList) {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_8);
        out << data;
        theClient->write(block);
    }

    if(inputBuffer.count() >0)
    {
        for(int i =0; i < inputBuffer.count(); i++)
        {
            foreach (QTcpSocket* theClient, userList) {
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_8);
                out << inputBuffer.at(i);
                theClient->write(block);
            }
        }

        inputBuffer.clear();
    }

    m_isBusy = false;

}
