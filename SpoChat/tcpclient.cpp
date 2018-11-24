#include <tcpclient.h>
#include <QTimer>

TcpClient::TcpClient(PeerList *listOfPeer, QObject *parent) : QObject(parent){
    this->peerList= listOfPeer;
    this->tcpServer = new QTcpServer(this);

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

void TcpClient::slotNewConnection(){
    // получаем сокет нового входящего соединения

    QTcpSocket *socket = tcpServer->nextPendingConnection();
    PeerTag* tag = peerList->searchByIp(socket->peerAddress().toString());//получили тег полльзователя, от которого пришло сообщение
    if (tag->getPeerSocket()==nullptr){
        qDebug()<<"SLOT NEW CONNECTION FROM SOCKETSERVER FOR"<<tag->getUserName();
        tag->setPeerSocket(socket);
        connect (socket, SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
        connect (socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
        connect (socket, SIGNAL(connected()), this, SLOT(slotConnected()));
        connect (socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    }
}

void TcpClient::slotSendTo(QString nickName,QString groupName,QString messageTo){
    PeerTag* tag = peerList->searchByName(groupName);
    //Если подключения по сокету пользователя ещё не было
    //tag->getPeerSocket()->isValid()
    if (tag->getPeerSocket()==nullptr){
        qDebug()<<"TcpClient: i find "<<tag->getUserName()<<"for conncetion";

        QTcpSocket* socket = new QTcpSocket(this);
        tag->setPeerSocket(socket);
        connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
        connect (socket, SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
        socket->connectToHost(tag->getIp(),4540);
    }

    //формирует сообщение
    QString output;
    output = nickName+"@"+nickName+"@"+messageTo;

    auto sendCallback=[tag,this,output]()
    {
        tag->getPeerSocket()->write(output.toUtf8());
        emit signalSendToGraphics(output);
        //tag->getPeerSocket()->flush();
    };

    if (QAbstractSocket::ConnectedState==tag->getPeerSocket()->state())
        sendCallback();
    else
        connect(tag->getPeerSocket(),&QAbstractSocket::connected,this,sendCallback);

}

void TcpClient::slotConnected(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    emit signalSendToLog("connection to " + socket->peerAddress().toString());
    qDebug()<<"TcpClient: connection to user"<<socket->peerName();
}
void TcpClient::slotDisconnected(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    emit signalSendToLog("disconnect from" + socket->peerAddress().toString());
    qDebug()<<"TcpClient: disconnect from"<<socket->peerName();
}

void TcpClient::slotError(QAbstractSocket::SocketError){
    QTcpSocket *socket = (QTcpSocket*)sender();
    emit signalSendToLog("error" + socket->peerAddress().toString()+socket->errorString());
    qDebug()<<"TcpClient: error"<<socket->peerName() + socket->errorString();
}
void TcpClient::slotReadMessage(){
    qDebug()<<"Мы в слоте ридамессадж";
    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
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
        in >> str;
        nextBlockSize = 0;
        qDebug() << "TcpClient: Recieved " + str;
        emit signalSendToGraphics(str);
    }
}
