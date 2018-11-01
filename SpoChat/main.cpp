#include "mainwindow.h"
#include "peerlist.h"
#include "udpclient.h"
#include "udpserver.h"
#include "peerlist.h"
#include <QApplication>
#include <QDebug>
#include "peertag.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*!
     * Объявляем Список клиентов, который будет использоваться для отправки сообщений, и который будет заполняться в Server
     */
    PeerList _peerList;
    /*!
     * объявляем udpклиента,который будет посылать сообщения от нас
     */
    UdpClient _client;
    /*!
     *объявляем сервер,который будет принимать сообщения о присутствии онлайн от пользователей, в том числе и от нас
    */
    UdpServer server(&_peerList);


    return a.exec();
}
