#ifndef TCPPACKAGER_H
#define TCPPACKAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDateTime>

#define masterKey "theUltimateKey"
#define theSecretKey "fountainController"
class tcpPackager
{

    static QByteArray m_scecretKey;

public:
    static QString m_clientId;
#if defined(Q_OS_MAC) || defined(Q_OS_WIN) || defined(Q_OS_UNIX)
    static constexpr int m_clientType = 0;
#else
    constexpr int m_clientType = 1;
#endif
    tcpPackager();
    static QString generateClientId();
    static QByteArray playProgram(const QString &programName, const QByteArray &Program);
    static QByteArray playSpeed(const QByteArray &data);
    static QByteArray isFountainOnline();
    static QByteArray fountainResponse(const QByteArray &response);
    static QByteArray fountainStatus(const bool &status);
    static QByteArray fountainCurrentPlayingProgram(const QString &program);
    static QByteArray updateSecretKey(const QString &key);

    static bool isPackageValid(const QByteArray &input);
    static QJsonObject packageToJson(const QByteArray &input);
    static QByteArray AnswerWhoIsControlling(const QString &clientId, const int &clientType);
    static QByteArray AskWhoIsControlling();
    static QByteArray requestToAddNewClient();
    static QByteArray requestToGetPermission();
    static QByteArray aboutToDisconnect();
    static QByteArray sendBinfile(const quint8 BOX_ID, const QString &fileURL);
    static void setSecretKey(const QByteArray &newKey);



};

#endif // TCPPACKAGER_H
