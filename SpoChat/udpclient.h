#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>
#include <QMap>

#include "clienttag.h"
#include "idgenerator.h"

class UdpClient : public QObject
{
    Q_OBJECT
private:
    QString _userName = "Name";
public:
    explicit UdpClient(QObject *parent = 0);
    IdGenerator *id;
    QTimer *_timer;

    QList<QUdpSocket*> _udpSocketList;
    QList<QHostAddress> _addressList;

    //QMap<QHostAddress,QUdpSocket*> _mapAddressSocket;

    QString getUserName()const;
    void setUserName(QString name);
public slots:
    void sendDatagram();
};

#endif // UDPCLIENT_H
