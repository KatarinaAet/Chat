
#include "udpserver.h"

UdpServer::UdpServer(PeerList *clientList, QObject *parent) : QObject(parent)
{
    this->_peerList = clientList;

    this->socketUdpServer = new QUdpSocket(this);
    if(socketUdpServer->bind(45000,QUdpSocket ::ShareAddress)){
        connect(socketUdpServer, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
        qDebug() << "QHostAddress::Any bound successfully.";
    }
    else{
        qDebug() << "UdpServer: Port in use. Change port!";
        qDebug() << "QHostAddress::Any bound wasn't successfully.";
        socketUdpServer->deleteLater();
    }
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
            correctMessage = StringList;
    }

    PeerTag *newPeerTag = new PeerTag(this);
    QHostInfo HI = QHostInfo::fromName(senderAddr.toString());

    newPeerTag->setTime(QTime::currentTime().toString());
    newPeerTag->setUserName(correctMessage[3]);
    newPeerTag->setHostName(HI.hostName());
    newPeerTag->setIp(senderAddr.toString());
    newPeerTag->setPort(senderPort);
    newPeerTag->setUuid(correctMessage[4]);

    if (correctMessage[2] == mesOnlineByteArr){
        _peerList->slotNewPeerTag(newPeerTag);
    }

    //QStringList s=_peerList->printPeerList();
    //delete(newPeerTag);
    correctMessage.clear();
}
