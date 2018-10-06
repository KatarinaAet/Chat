#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

#include "clienttag.h"
#include "idgenerator.h"

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = 0);
    IdGenerator *id;
    QTimer *_timer;
    QList<QUdpSocket*> _udpSocketList;
    QList<QHostAddress> _addressList;

public slots:
    void sendDatagram();
};

#endif // UDPCLIENT_H
