//udpserver.cpp
#include "udpserver.h"

UdpServer::UdpServer(PeerList *clientList, QObject *parent) : QObject(parent)
{
    this->_peerList = clientList;

    QUdpSocket *_serverSocket = new QUdpSocket(this);
    if(_serverSocket->bind(45000,QUdpSocket ::ShareAddress)){
        connect(_serverSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
        qDebug() << "QHostAddress::Any" << QHostAddress::Any << "bound successfully.";
        _udpServSocketList.append(_serverSocket);
    }
    else{
        qDebug() << "UdpServer: Port in use. Change port!";
        qDebug() << "QHostAddress::Any" << QHostAddress::Any<< "bound wasn't successfully.";
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
            /*!
             * Разделяем присланное сообщение на символ начала строки, "длину сообщения" "сообщение","UserName","Uuid" по ";"
             * сообщение начинается с "@"
            */
            QStringList StringList = dataStr.split(";");

            //! Делаем проверку на корректность доставки
            if((StringList[0]!="@")||(StringList[1].toInt()!= (dataStr.length()-(StringList[0]+";"+StringList[1]+";").length()))){
                qDebug()<<"There was a data loss at the time of sending";
                break;
            }
            PeerTag *newPeerTag;
            newPeerTag = new PeerTag(this);
            QHostInfo HI = QHostInfo::fromName(senderAddr.toString());

            newPeerTag->setTime(QTime::currentTime().toString());
            newPeerTag->setUserName(StringList[3]);
            newPeerTag->setHostName(HI.hostName());
            newPeerTag->setIp(senderAddr.toString());
            newPeerTag->setPort(senderPort);
            newPeerTag->setUuid(StringList[4]);
            if (StringList[2] == mesOnlineByteArr){
                _peerList->slotNewPeerTag(newPeerTag);
            }
    }
    QStringList s=_peerList->printPeerList();
}
