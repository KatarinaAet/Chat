//udpserver.cpp
#include "udpserver.h"
#include "clientlist.h"
#include "QNetworkInterface"
#include "udpclient.h"

UdpServer::UdpServer(ClientList *clientList, QObject *parent) : QObject(parent)
{
    this->_clientList = clientList;

    foreach (QHostAddress address, QNetworkInterface::allAddresses() ){
        if((address.toString().contains(".")) && (address.toString()!="127.0.0.1")){
            QUdpSocket *_serverSocket = new QUdpSocket(this);
            if (_serverSocket->bind(address,45000,  QUdpSocket :: ShareAddress | QUdpSocket::ReuseAddressHint)){
                connect(_serverSocket, &QUdpSocket::readyRead, this,&UdpServer::processPendingDatagrams, Qt::QueuedConnection);
                qDebug()<<address.toString()<<"bound successfully.";
                /*!
                 * добавляем новые сокеты в список сокетов сервера для последующего bind
                 */
                _udpServSocketList.append(_serverSocket);
            }
            else{
                qDebug() <<"UdpServer: Port in use. Change port!";
                qDebug()<<address.toString()<<"bound wasn't successfully.";
                _serverSocket->deleteLater();
            }
        }
    }

    QUdpSocket *_serverSocket = new QUdpSocket(this);
    if(_serverSocket->bind(45000,QUdpSocket ::ShareAddress)){
        connect(_serverSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
        qDebug() << "QHostAddress::Any" << QHostAddress::Any << "bound successfully.";
        _udpServSocketList.append(_serverSocket);
    }
    else{
        qDebug() << "UdpServer: Port in use. Change port!";
        qDebug() << "ZERO" << "bound wasn't successfully.";
        _serverSocket->deleteLater();
    }

    qDebug()<<"number of server socket"<<_udpServSocketList.size();
    qDebug()<<"ServSocketList ::"<<_udpServSocketList;
    return;
}


void UdpServer::processPendingDatagrams()
{
    QUdpSocket *socketServ = (QUdpSocket*)sender();

    QByteArray datagram, mesOnlineByteArr;
    quint16 senderPort;
    QHostAddress senderAddr;
    QString mesOnline = "Here";

    mesOnlineByteArr = mesOnline.toLocal8Bit();

    while(socketServ->hasPendingDatagrams()){

            datagram.resize(socketServ->pendingDatagramSize());
            socketServ->readDatagram(datagram.data(),datagram.size(),&senderAddr,&senderPort);

            QString dataStr = datagram.data();
            QStringList StringList = dataStr.split(";");

            ClientTag *newClientTag;
            newClientTag = new ClientTag(this);
            QHostInfo HI = QHostInfo::fromName(senderAddr.toString());

            newClientTag->setTime(QTime::currentTime().toString());
            newClientTag->setName(HI.hostName());
            newClientTag->setIp(senderAddr.toString());
            newClientTag->setPort(senderPort);
            newClientTag->setUuid(StringList[1]);


            if (StringList[0] == mesOnlineByteArr){
                _clientList->slotNewClientTag(newClientTag);
            }
    }
    QStringList s=_clientList->printClientList();
}
