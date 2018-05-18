#ifndef BRIDGESERVER_H
#define BRIDGESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>

class bridgeServer: public QObject
{

    Q_OBJECT

    int m_ServerPOrt;

    QTcpServer *m_bridgeServer;
    QList<QTcpSocket*> userList;
    QDataStream in;
    bool m_isBusy;
    QList<QByteArray> inputBuffer;

private slots:
    void newConnectionHandler();
    void readyReadHandler();
    void clientDiskConnectedHandler();
    void socketErrorHandler(QAbstractSocket::SocketError err);

public slots:

    void fromFountainDevices(const QByteArray &data);
    void writeToUser(const QByteArray &data);

signals:

    void toFountainDevices(const QByteArray &data);
    void letWriteToUser(const QByteArray &data);


public:
    explicit bridgeServer(const int &port, QObject * parent = nullptr);
    void start();
};

#endif // BRIDGESERVER_H
