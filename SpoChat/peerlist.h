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
#include "peertag.h"

class PeerList : public QObject
{
    Q_OBJECT
public:
    PeerList();
//private:
    QList <PeerTag*> list;
signals:
    void newPeer(const QString &name);
    void removePeer(const QString &name);
public slots:
    void slotNewPeerTag(PeerTag* client);
    QStringList printPeerList();
    PeerTag* searchByName(QString name); // Возвращает пользователя с заданным никнеймом
    PeerTag* searchByIp(QString ip);

    void refreshList();
};

#endif // CLIENTLIST_H
