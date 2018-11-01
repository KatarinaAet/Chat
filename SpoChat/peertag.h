#ifndef CLIENTTAG_H
#define CLIENTTAG_H

#include <QObject>
#include <QUdpSocket>
#include <QTime>
#include <QDebug>
#include <QHostInfo>
#include <QUuid>
#include <QTcpSocket>


class PeerTag : public QObject
{
    Q_OBJECT
public:
    explicit PeerTag(QObject *parent = 0);
private:
    QString _userName = "";
    QString _hostName = "";
    QString _ipAddr = "";
    QString _time = "";
    int _port = 45000;
    QString _uuid; //!unique user id

    QTcpSocket* _socketForTcpClient = new QTcpSocket(this);
public:
    QString getUserName()const;
    QString geHosttName() const;
    QString getIp() const;
    QString getTime() const;
    int getPort() const;
    QString getUuid() const;

    void setUserName(QString name);
    void setHostName(QString str);
    void setIp(QString str);
    void setTime(QString str);
    void setPort(int num);
    void setUuid(QString uuid);

    QString printInfo();

    bool operator ==( const PeerTag & client2)
    {
        return ((this->getUuid() == client2.getUuid()));

    }
    PeerTag& operator =(const PeerTag & client2){

        this->setUserName(client2.getUserName());
        this->setHostName(client2.geHosttName());
        this->setIp(client2.getIp());
        this->setTime(client2.getTime());
        this->setPort(client2.getPort());
        this->setUuid(client2.getUuid());

        return *this;
    }
};

#endif // CLIENTTAG_H
