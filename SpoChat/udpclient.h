#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

#include "peertag.h"
#include "idgenerator.h"

class UdpClient : public QObject
{
    Q_OBJECT
private:
    QString _userName = "Da";
public:
    explicit UdpClient(QObject *parent = 0);
    IdGenerator *id;
    QTimer *_timer;
    QUdpSocket *_udpSocket;
    QList<QHostAddress> _addressList;

public slots:
    void sendDatagram();
    void slotSetUserName(QString name);
    QString slotGetUserName()const;

};

#endif // UDPCLIENT_H
