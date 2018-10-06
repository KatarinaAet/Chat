//clienttag.cpp
#include "clienttag.h"

ClientTag::ClientTag(QObject *parent) : QObject(parent){
}
void ClientTag::setIp(QString str){
    _ipAddr = str;
}
QString ClientTag::getIp() const{
    return _ipAddr;
}
void ClientTag::setName(QString str){
    _userName = str;
}
QString ClientTag::getName() const{
    return _userName;
}
int ClientTag::getPort() const{
    return _port;
}
void ClientTag::setPort(int num){
    _port = num;
}
QString ClientTag::getTime()const{
    return _time;
}
void ClientTag::setTime(QString newTime){
    _time = newTime;
}

QString ClientTag::getUuid() const{
    return _uuid;
}
void ClientTag::setUuid(QString id){
    _uuid = id;
}
QString ClientTag::printInfo(){
    QString info = "";
    info.append(getIp() + " " + getName() + " " + QString::number(getPort()) + " " + getTime());
    return info;
}
