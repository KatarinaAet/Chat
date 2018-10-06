//clientlist.cpp
#include "clientlist.h"
#include "udpclient.h"
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QFile>

ClientList::ClientList(){
    QTimer *_timer2 = new QTimer();
    connect(_timer2, SIGNAL(timeout()), this, SLOT(refreshList()));
    _timer2->start(10*1000);
    /*!
    *каждый промежуток времени список пользователей будет проверяться на активность
    */
}

void ClientList::slotNewClientTag(ClientTag *clientTag){
    for (auto pClient:list){
        if (*pClient == *clientTag){
            pClient->setTime(QTime::currentTime().toString());
            /*!
             * обновляем время у клиента
             */
            qDebug() << "ClientList:"<<pClient->getIp()<< " No need in append";
            return;
        }
    }
    list.append(clientTag);
    return;
}

QStringList ClientList::printClientList(){
    QStringList infoList;
    for (auto pClient:list){
        infoList.append(pClient->printInfo());
        qDebug()<<"ClientList::printClientList : "<<pClient->printInfo();
    }
    return infoList;
}

void ClientList::refreshList(){
    /*!
     * проверка клиентов на активность
     */
    qDebug() << "ClientList: Refreshing";
    for (int i = 0; i < list.size(); i++){
        QTime time = QTime::fromString(list[i]->getTime(), "hh:mm:ss");
        QTime now = QTime:: currentTime();
        int diff = time.msecsTo(now);
        if (diff > 9*1000){
            list.removeAt(i);
        }
    }
}
