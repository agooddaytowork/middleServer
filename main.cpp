#include <QCoreApplication>
#include "bridgeserver.h"
#include "fountainclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    fountainClient box00("10.0.0.3",8080);
    fountainClient box01("10.0.0.4",8080);
    fountainClient box02("10.0.0.5",8080);
    fountainClient box03("10.0.0.6",8080);
    fountainClient box04("10.0.0.7",8080);
    fountainClient box05("10.0.0.8",8080);
    fountainClient box06("10.0.0.9",8080);


    bridgeServer theServer(8080);

    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box00,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box01,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box02,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box03,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box04,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box05,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box06,SLOT(inPut(QByteArray)));

    QObject::connect(&box00,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box01,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box02,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box03,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box04,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box05,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box06,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));


    theServer.start();
    box00.start();
    box01.start();
    box02.start();
    box03.start();
    box04.start();
    box05.start();
    box06.start();

    return a.exec();
}
