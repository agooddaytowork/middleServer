#ifndef FOUNTAINCLIENT_H
#define FOUNTAINCLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QTimer>
#include <QAbstractSocket>
#include <QDataStream>
#include <QDebug>


class fountainClient : public QObject
{

    Q_OBJECT

    QDataStream in;
    QTcpSocket* m_fountainClient;

    QString m_IP;
    int m_Port;

    QList<QByteArray> inputBuffer;
    bool m_isBusy;
    bool m_isConnected;

    QTimer* m_TimeOutTimer;


private slots:

    void connectedHandler();
    void disconnectedHandler();
    void errorHandler(QAbstractSocket::SocketError err);
    void readyReadHandler();

public slots:
    void inPut(const QByteArray &data);
    void write(const QByteArray &data);

signals:

    void out(const QByteArray &data);
    void letstWrite(const QByteArray &data);
    void writeFinished();
public:
    explicit fountainClient(const QString &m_IP, const int &m_Port, QObject * parent = nullptr);

    void start();
};

#endif // FOUNTAINCLIENT_H
