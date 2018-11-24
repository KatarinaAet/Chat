#include "idgenerator.h"
#include <QNetworkInterface>
#include <QSet>

IdGenerator::IdGenerator(QObject *parent) : QObject(parent)
{
}

QString IdGenerator::genId()
{
    QStringList _macAddr;
    QSet<QString> addresses;
    foreach (QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            QHostAddress broadcastAddress = entry.broadcast();
            if (broadcastAddress != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost) {
                /*_macAddr*/addresses.insert(interface.hardwareAddress());
            }
        }
    }

    return QString::number(qHash(addresses));
}

