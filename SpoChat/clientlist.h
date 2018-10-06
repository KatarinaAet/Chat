#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QtNetwork>
#include "udpclient.h"
#include "clienttag.h"

class ClientList : public QObject
{
    Q_OBJECT
public:
    ClientList();
private:
    QList <ClientTag*> list;
public slots:
    void slotNewClientTag(ClientTag* client);
    QStringList printClientList();
    void refreshList();
};

#endif // CLIENTLIST_H
