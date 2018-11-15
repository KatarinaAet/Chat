#include "tcpserver.h"

TcpServer::TcpServer(PeerList* peerList,QObject *parent):QObject (parent)
{
    tcpServer = new QTcpServer(this);
    this->peerList = peerList;

    if (tcpServer->listen(QHostAddress::Any,4540)){
        connect(tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
        qDebug() << "TcpServer: listen";
    }
    else{
        qDebug() << "TcpServer: Unable to listen " + tcpServer->errorString();
        tcpServer->close();
        return;
    }
}

void TcpServer::slotNewConnection(){
    // получаем сокет нового входящего соединения

    QTcpSocket *socket = tcpServer->nextPendingConnection();
    PeerTag* tag = peerList->searchByIp(socket->peerAddress().toString());//получили тег полльзователя, от которого пришло сообщение
    if (tag->getPeerSocket()==nullptr){
        qDebug()<<"TcpServer: I HAVE A NEW PEOPLE"<<tag->getUserName();
        tag->setPeerSocket(socket);
        connect (tag->getPeerSocket(), SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
        connect (tag->getPeerSocket(), SIGNAL(disconnected()), this, SLOT(deleteLater()));
        connect (tag->getPeerSocket(), SIGNAL(connected()), this, SLOT(slotConnected()));
        connect (tag->getPeerSocket(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    }
}


void TcpServer::slotReadMessage()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!nextBlockSize) {
            if (socket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }
        if (socket->bytesAvailable() < nextBlockSize) {
            break;
        }
        QString str;
        in >>  str;
        nextBlockSize = 0;

        qDebug() << "TcpServer: Recieved " + str;
        emit signalSendToGraphics(str);

        //in.flush();
    }
    //socket->flush();

}
void TcpServer::slotConnected(){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("TcpServer: connection to " + socket->peerAddress().toString());
    qDebug()<<"tcpServer: connection to user"<<socket->peerName();

}

void TcpServer::slotDisconnected(){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("_______DISSCONNECT_________" + socket->peerAddress().toString());
}

void TcpServer::slotError(QAbstractSocket::SocketError){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("_________ERROR____" + socket->peerAddress().toString()+socket->errorString());
}
