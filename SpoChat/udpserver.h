#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include <QDebug>
#include "udpclient.h"
#include "peerlist.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QList>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(PeerList *clientList, QObject *parent=0);
private:
    PeerList *_peerList;
    QList<QUdpSocket*> _udpServSocketList;
    QUdpSocket * socketUdpServer;
    QStringList correctMessage;

public slots:
    void processPendingDatagrams();
};

#endif // UDPSERVER_H
