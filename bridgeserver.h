#ifndef BRIDGESERVER_H
#define BRIDGESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class bridgeServer: public QObject
{

    Q_OBJECT

    int m_ServerPOrt;

    QTcpServer *m_bridgeServer;
    QList<QTcpSocket*> userList;
    QDataStream in;
    bool m_isBusy;
    QList<QByteArray> inputBuffer;
    QTimer* m_TimeOutTimer;

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
    void toBox00(const QByteArray &data);
    void toBox01(const QByteArray &data);
    void toBox02(const QByteArray &data);
    void toBox03(const QByteArray &data);
    void toBox04(const QByteArray &data);
    void toBox05(const QByteArray &data);
    void toBox06(const QByteArray &data);
    void toBox07(const QByteArray &data);

    void letWriteToUser(const QByteArray &data);


public:
    explicit bridgeServer(const int &port, QObject * parent = nullptr);
    void start();
};

#endif // BRIDGESERVER_H
