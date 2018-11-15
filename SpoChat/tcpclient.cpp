#include <tcpclient.h>

TcpClient::TcpClient(PeerList *listOfPeer, QObject *parent) : QObject(parent){
    this->peerList= listOfPeer;
}

void TcpClient::slotSendTo(QString nickName,QString groupName,QString messageTo){
    PeerTag* tag = peerList->searchByName(nickName);
    //Если подключения по сокету пользователя ещё не было
    //tag->getPeerSocket()->isValid()
    if (tag->getPeerSocket()==nullptr){
        qDebug()<<"TcpClient: I FIND YOU"<<tag->printInfo();


        QTcpSocket* socket = new QTcpSocket(this);
        tag->setPeerSocket(socket);
        connect(socket, SIGNAL(connected()), this, SLOT(slotConnected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
        connect (socket, SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
        socket->connectToHost(tag->getIp(),4540);
    }

    //формирует сообщение
//    QByteArray  arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    QString output;
    output = nickName+"@"+groupName+"@"+messageTo;
//    out << quint16(0) << output;
//    out.device()->seek(0);
//    out << quint16(arrBlock.size() - sizeof(quint16));

    auto sendCallback=[tag,this,output]()
    {
        tag->getPeerSocket()->write(output.toUtf8());
        emit signalSendToGraphics(output);
        tag->getPeerSocket()->flush();
    };

    if (QAbstractSocket::ConnectedState==tag->getPeerSocket()->state())
        sendCallback();
    else
        connect(tag->getPeerSocket(),&QAbstractSocket::connected,this,sendCallback);

}

void TcpClient::slotConnected(){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("connection to " + socket->peerAddress().toString());
    qDebug()<<"TcpClient: connection to user"<<socket->peerName();
}

void TcpClient::slotDisconnected(){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("disconnect from" + socket->peerAddress().toString());
    qDebug()<<"TcpClient: disconnect from"<<socket->peerName();
}

void TcpClient::slotError(QAbstractSocket::SocketError){
    QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    emit signalSendToLog("error" + socket->peerAddress().toString()+socket->errorString());
    qDebug()<<"TcpClient: error"<<socket->peerName() + socket->errorString();
}
void TcpClient::slotReadMessage()
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

        qDebug() << "TcpClient: Recieved " + str;
        emit signalSendToGraphics(str);
        //in.flush();
    }
}
