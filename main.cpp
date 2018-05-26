#include <QCoreApplication>
#include "bridgeserver.h"
#include "fountainclient.h"

#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QThread thread00;
    QThread thread01;
    QThread thread02;
    QThread thread03;
    QThread thread04;
    QThread thread05;
    QThread thread06;
    QThread thread07;
    QThread threadSever;

    fountainClient box00("10.0.0.2",8080);
    fountainClient box01("10.0.0.3",8080);
    fountainClient box02("10.0.0.4",8080);
    fountainClient box03("10.0.0.5",8080);
    fountainClient box04("10.0.0.6",8080);
    fountainClient box05("10.0.0.7",8080);
    fountainClient box06("10.0.0.8",8080);
    fountainClient box07("10.0.0.9",8080);
    bridgeServer theServer(8080);

    box00.moveToThread(&thread00);
    box01.moveToThread(&thread01);
    box02.moveToThread(&thread02);
    box03.moveToThread(&thread03);
    box04.moveToThread(&thread04);
    box05.moveToThread(&thread05);
    box06.moveToThread(&thread06);
    box07.moveToThread(&thread07);

    theServer.moveToThread(&threadSever);


    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box00,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box01,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box02,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box03,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box04,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box05,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box06,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toFountainDevices(QByteArray)),&box07,SLOT(inPut(QByteArray)));

    QObject::connect(&theServer,SIGNAL(toBox00(QByteArray)),&box00,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox01(QByteArray)),&box01,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox02(QByteArray)),&box02,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox03(QByteArray)),&box03,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox04(QByteArray)),&box04,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox05(QByteArray)),&box05,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox06(QByteArray)),&box06,SLOT(inPut(QByteArray)));
    QObject::connect(&theServer,SIGNAL(toBox07(QByteArray)),&box07,SLOT(inPut(QByteArray)));

    QObject::connect(&box00,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box01,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box02,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box03,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box04,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box05,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box06,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));
    QObject::connect(&box07,SIGNAL(out(QByteArray)),&theServer,SLOT(fromFountainDevices(QByteArray)));

    QObject::connect(&thread00,&QThread::started,&box00,&fountainClient::start);
    QObject::connect(&thread01,&QThread::started,&box01,&fountainClient::start);
    QObject::connect(&thread02,&QThread::started,&box02,&fountainClient::start);
    QObject::connect(&thread03,&QThread::started,&box03,&fountainClient::start);
    QObject::connect(&thread04,&QThread::started,&box04,&fountainClient::start);
    QObject::connect(&thread05,&QThread::started,&box05,&fountainClient::start);
    QObject::connect(&thread06,&QThread::started,&box06,&fountainClient::start);
    QObject::connect(&thread07,&QThread::started,&box07,&fountainClient::start);
    QObject::connect(&threadSever,&QThread::started,&theServer,&bridgeServer::start);

    thread00.start();
    thread01.start();
    thread02.start();
    thread03.start();
    thread04.start();
    thread05.start();
    thread06.start();
    thread07.start();
    threadSever.start();

    return a.exec();
}
