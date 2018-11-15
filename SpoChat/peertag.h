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
    QTcpSocket* _socketForTcpClient = nullptr;

public:

    QString getUserName()const;
    QString getHostName() const;
    QString getIp() const;
    QString getTime() const;
    int getPort() const;
    QString getUuid() const;
    QTcpSocket *getPeerSocket() const;

    void setUserName(QString name);
    void setHostName(QString str);
    void setIp(QString str);
    void setTime(QString str);
    void setPort(int num);
    void setUuid(QString uuid);
    void setPeerSocket(QTcpSocket *socket);


    QString printInfo();

    bool operator ==( const PeerTag & client2){
        return ((this->getUuid() == client2.getUuid()));

    }
    PeerTag& operator =(const PeerTag & peer2){
        this->setUserName(peer2.getUserName());
        this->setHostName(peer2.getHostName());
        this->setIp(peer2.getIp());
        this->setTime(peer2.getTime());
        this->setPort(peer2.getPort());
        this->setUuid(peer2.getUuid());
        this->setPeerSocket(peer2.getPeerSocket());

        return *this;
    }
};

#endif // CLIENTTAG_H
