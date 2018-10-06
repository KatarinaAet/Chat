//udpclient.cpp
#include "udpclient.h"
#include <QNetworkInterface>


UdpClient::UdpClient(QObject *parent) : QObject(parent){
    id = new IdGenerator(this);
    _timer = new QTimer(this);
    /*
     * Создаем уникальный айди для пользователя
     */

    /*
     * каждые 5с будет отправляться датаграмма
     */
    connect(_timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));
    _timer->start(5*1000);

    /*
     * Ищем доступные сетевые интерфейсы и записываем в пользовательский список адресов доступные адреса для широковещательных запросов по ним
     */

    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost) {

                QUdpSocket * udpSocket = new QUdpSocket(this);
                _udpSocketList.append(udpSocket);

                _addressList.append(broadcastAddress);


            }
        }
    }

    qDebug()<<_addressList;

    qDebug()<<"List of Address"<<_addressList;

}

void UdpClient::sendDatagram(){
    QByteArray data = "Here;";
    data.append(id->genId());

    for (int i = 0; i<_udpSocketList.length(); i++){
        _udpSocketList[i]->writeDatagram(data,_addressList[i] , 45000);
        qDebug() << "UpdClient: " <<_udpSocketList[i]->localAddress().toString()<< QTime::currentTime().toString() << "my datagram has been sent to this address:" << _addressList[i];
    }

}
