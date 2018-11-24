//udpclient.cpp
#include "udpclient.h"
#include <QNetworkInterface>

UdpClient::UdpClient(QObject *parent) : QObject(parent){
    id = new IdGenerator(this);
    _timer = new QTimer(this);
    _udpSocket = new QUdpSocket(this);

    /*!
     * каждые 5с будет отправляться датаграмма
     */
    connect(_timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));
    _timer->start(3*1000);
    /*!
     * Ищем доступные сетевые интерфейсы и записываем в пользовательский
     * список адресов доступные адреса для широковещательных запросов по ним
     */
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();

            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost) {
                _addressList.append(broadcastAddress);
            }
        }

    }
    qDebug()<<"List of Address"<<_addressList;
}

void UdpClient::sendDatagram(){
    /*!
     * Описание метода посылки датаграммы
     * Здесь формируется посылаемй пакет
     */
    QByteArray data = "Here;";
    data.append(slotGetUserName()+";");
    data.append(id->genId());
    data.prepend(QByteArray::number(data.length())+";");
    data.prepend("@;");

    for (int i = 0; i<_addressList.length(); i++){
        _udpSocket->writeDatagram(data,_addressList[i] , 45000);
        //qDebug() << "UpdClient: " <<_udpSocket->localAddress().toString()<< QTime::currentTime().toString() << "my datagram has been sent to this address:" << _addressList[i];
    }
}

void UdpClient::slotSetUserName(QString name){
    _userName = name;
}

QString UdpClient::slotGetUserName()const{
    return _userName;
}
