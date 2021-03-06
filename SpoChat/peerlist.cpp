#include "peerlist.h"
#include "udpclient.h"
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QFile>

PeerList::PeerList(){
    QTimer *_timer2 = new QTimer();
    connect(_timer2, SIGNAL(timeout()), this, SLOT(refreshList()));
    _timer2->start(10*1000);
    /*!
    *каждый промежуток времени список пользователей будет проверяться на активность
    */
}

void PeerList::slotNewPeerTag(PeerTag *clientTag){
    for (auto pClient:list){
        if (*pClient == *clientTag){
            pClient->setTime(QTime::currentTime().toString());
            /*!
             * обновляем время у клиента
             */
            //qDebug() << "ClientList:"<<pClient->getIp()<< " No need in append";
            return;
        }
     }
    list.append(clientTag);

    qDebug() << "PeerList: append successful " << clientTag->getUserName();
    if (!(clientTag->getUserName().isEmpty())){
        emit newPeer(clientTag->getUserName());
        qDebug() << "SIGNAL ADD IS EMITTED";
    }
    else
        return;
}

QStringList PeerList::printPeerList(){
    QStringList infoList;
    for (auto pClient:list){
        infoList.append(pClient->printInfo());
        qDebug()<<"ClientList::printClientList : "<<pClient->printInfo();
    }
    return infoList;
}

void PeerList::refreshList(){
    //! проверка клиентов на активность
    qDebug() << "ClientList: Refreshing";
    for (int i = 0; i < list.size(); i++){
        QTime time = QTime::fromString(list[i]->getTime(), "hh:mm:ss");
        QTime now = QTime:: currentTime();
        int diff = time.msecsTo(now);
        if (diff > 9*1000){
            qDebug() << "ClientList: Refreshing was succesfull";
            //list[i]->getPeerSocket()->destroyed();
            emit removePeer(list[i]->getUserName());
            qDebug() << "SIGNAL removePeer is EMITTED";
            qDebug() << list[i]->getUserName();
            list.removeAt(i);
        }
    }
}

PeerTag* PeerList::searchByName(QString name){
    for(auto pClient:list){
        if(pClient->getUserName()==name){
            return pClient;
        }
    }
}

PeerTag* PeerList::searchByIp(QString ip){
    for(auto pClient:list){
        if(pClient->getIp()==ip){
            return pClient;
        }
    }
}

