#include "fountainclient.h"

fountainClient::fountainClient(const QString &m_IP, const int &m_Port,QObject *parent):QObject(parent), m_fountainClient(new QTcpSocket(this)), m_IP(m_IP), m_Port(m_Port), m_isBusy(false), m_isConnected(false)
{

        QObject::connect(m_fountainClient,SIGNAL(connected()),this,SLOT(connectedHandler()));
        QObject::connect(m_fountainClient,SIGNAL(disconnected()),this,SLOT(disconnectedHandler()));
        QObject::connect(m_fountainClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorHandler(QAbstractSocket::SocketError)));
        QObject::connect(m_fountainClient,SIGNAL(readyRead()),this,SLOT(readyReadHandler()));
        QObject::connect(this,SIGNAL(letstWrite(QByteArray)),this,SLOT(write(QByteArray)));



        in.setDevice(m_fountainClient);
        in.setVersion(QDataStream::Qt_5_8);

        inputBuffer.clear();

}


void fountainClient::start()
{
    m_fountainClient->connectToHost(m_IP, m_Port);
}

void fountainClient::connectedHandler()
{
    m_isConnected = true;

    if(inputBuffer.count() >0)

    {
        QByteArray data = inputBuffer.at(0);
        inputBuffer.removeFirst();
        emit letstWrite(data);
    }
}

void fountainClient::disconnectedHandler()
{
    m_isConnected = false;
}

void fountainClient::errorHandler(QAbstractSocket::SocketError err)
{

    qDebug() << "Error handler: IP " + m_IP;
    switch (err) {
    case QAbstractSocket::ConnectionRefusedError:

        QTimer::singleShot(30000,this,&fountainClient::start);
        qDebug() << "ConnectionRefusedError";
        break;

    case QAbstractSocket::RemoteHostClosedError:
        QTimer::singleShot(30000,this,&fountainClient::start);
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

void fountainClient::readyReadHandler()
{

    in.startTransaction();

    QByteArray result;

    in >> result;
    if(!in.commitTransaction()) return;

    emit out(result);
}


void fountainClient::inPut(const QByteArray &data)
{

    if(!m_isBusy && m_isConnected)
    {
        emit letstWrite(data);
    }
    else
    {
        start();
        inputBuffer.append(data);
    }

}
void fountainClient::write(const QByteArray &data)
{

    m_isBusy = true;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << data;
    m_fountainClient->write(block);

    if(inputBuffer.count() != 0)
    {
        for(int i =0; i < inputBuffer.count();i++)
        {
            out << inputBuffer.at(i);
             m_fountainClient->write(block);
        }

        inputBuffer.clear();
    }

    m_isBusy = false;

}


