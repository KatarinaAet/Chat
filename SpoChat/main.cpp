#include "mainwindow.h"
#include "peerlist.h"
#include "udpclient.h"
#include "udpserver.h"
#include "peerlist.h"
#include <QApplication>
#include <QDebug>
#include "peertag.h"
#include <tcpserver.h>
#include <tcpclient.h>
#include <graphics.h>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    /*!
     * Объявляем Список клиентов, который будет использоваться для отправки сообщений об онлайне пользователя, и который будет заполняться в Server
     */
    PeerList * peerList= new PeerList();
    Graphics* graphics = new Graphics(peerList);
    /*!
     * объявляем udpклиента,который будет посылать сообщения об онлайне от нас и от других пользователей
     */
    UdpClient* clientUdp = new UdpClient();
    /*!
     *объявляем сервер,который будет принимать сообщения о присутствии онлайн от пользователей, в том числе и от нас
    */
    UdpServer* serverUdp = new UdpServer(peerList) ;

    TcpClient* clientTcp = new TcpClient(peerList);


    QObject::connect(graphics, SIGNAL(signalSendToClient(QString,QString,QString)),clientTcp,SLOT(slotSendTo(QString,QString,QString)));
    QObject::connect(clientTcp, SIGNAL(signalSendToGraphics(QString)),graphics,SLOT(slotReceiveMessage(QString)));
    QObject::connect(clientTcp, SIGNAL(signalSendToLog(QString)),graphics,SLOT(slotLog(QString)));





    graphics->show();
    return a.exec();
}
