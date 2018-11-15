//clienttag.cpp
#include "peertag.h"

PeerTag::PeerTag(QObject *parent) : QObject(parent){
}
void PeerTag::setUserName(QString name){
    _userName = name;
}
QString PeerTag::getUserName() const{
    return _userName;
}
void PeerTag::setIp(QString str){
    _ipAddr = str;
}
QString PeerTag::getIp() const{
    return _ipAddr;
}
void PeerTag::setHostName(QString str){
    _hostName = str;
}
QString PeerTag::getHostName() const{
    return _hostName;
}
int PeerTag::getPort() const{
    return _port;
}
void PeerTag::setPort(int num){
    _port = num;
}
QString PeerTag::getTime()const{
    return _time;
}
void PeerTag::setTime(QString newTime){
    _time = newTime;
}
QString PeerTag::getUuid() const{
    return _uuid;
}
void PeerTag::setUuid(QString id){
    _uuid = id;
}
QString PeerTag::printInfo(){
    QString info = "";
    info.append(getIp() + " " + getHostName() + " " + QString::number(getPort()) + " " + getTime() + " "+getUserName());
    return info;
}
QTcpSocket *PeerTag::getPeerSocket() const
{
    return _socketForTcpClient;
}

void PeerTag::setPeerSocket(QTcpSocket *socket)
{
    _socketForTcpClient = socket;
}
