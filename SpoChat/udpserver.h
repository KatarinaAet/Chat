#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include <QDebug>
#include "udpclient.h"
#include "clientlist.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QList>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(ClientList *clientList, QObject *parent=0);
private:
    ClientList *_clientList;
    QList<QUdpSocket*> _udpServSocketList;

public slots:
    void processPendingDatagrams();
};

#endif // UDPSERVER_H
