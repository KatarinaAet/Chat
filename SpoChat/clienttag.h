#ifndef CLIENTTAG_H
#define CLIENTTAG_H

#include <QObject>
#include <QUdpSocket>
#include <QTime>
#include <QDebug>
#include <QHostInfo>
#include <QUuid>

class ClientTag : public QObject
{
    Q_OBJECT
public:
    explicit ClientTag(QObject *parent = 0);
private:
    QString _userName = "";
    QString _ipAddr = "";
    QString _time = "";
    int _port = 45000;
    QString _uuid;
public:
    QString getIp() const;
    QString getName() const;
    QString getTime() const;
    int getPort() const;
    QString getUuid() const;

    void setIp(QString str);
    void setName(QString str);
    void setTime(QString str);
    void setPort(int num);
    void setUuid(QString uuid);

    QString printInfo();

    bool operator ==( const ClientTag & client2)
    {
        return ((this->getUuid() == client2.getUuid()));

    }
    ClientTag& operator =(const ClientTag & client2){
        this->setIp(client2.getIp());
        this->setName(client2.getName());
        this->setTime(client2.getTime());
        this->setPort(client2.getPort());
        return *this;
    }
};

#endif // CLIENTTAG_H
