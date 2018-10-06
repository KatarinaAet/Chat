#include "mainwindow.h"
#include "clientlist.h"
#include "udpclient.h"
#include "udpserver.h"
#include "clientlist.h"
#include <QApplication>
#include <QDebug>
#include "clienttag.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*!
     * Объявляем Список клиентов, который будет использоваться для отправки сообщений, и который будет заполняться в Server
     */
    ClientList _clientList;
    /*!
     * объявляем udpклиента,который будет посылать сообщения от нас
     */
    UdpClient _client;
    /*!
     *объявляем сервер,который будет принимать сообщения о присутствии онлайн от пользователей, в том числе и от нас
    */
    UdpServer server(&_clientList);


    return a.exec();
}
