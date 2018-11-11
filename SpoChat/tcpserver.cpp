#include "tcpserver.h"

tcpServer::tcpServer(QObject *parent):QObject (parent)
{
    tcpServ = new QTcpServer(this);
    if (tcpServ->listen(QHostAddress::Any,4540)){
        connect(tcpServ, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }
    else{
        qDebug() << "Unable to listen " + tcpServ->errorString();
        tcpServ->close();
        return;
    }
}

void tcpServer::slotNewConnection()
{
    /*!
     * получаем сокет нового входящего соединения
     */
    QTcpSocket *socket = tcpServ->nextPendingConnection();
    /*!
      * Проверяем сокет пира на nullptr
      */
    for (auto peer:peerL->list)
    {
        if (peer->getPeerSocket() == nullptr)
        {
            connect (peer->getPeerSocket(), SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
            connect (peer->getPeerSocket(), SIGNAL(disconnected()), this, SLOT(deleteLater()));
            //connect (peer->getPeerSocket(), SIGNAL(disconnected()), this, SLOT(disconnnectFromServer()));
            peer->setPeerSocket(socket);
            qDebug() << "TcpServer: got new socket";
        }

    }
}

void tcpServer::slotReadMessage()
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
            QTime   time;
            QString str;
            in >> time >> str;

            QString strMessage =
                time.toString() + " " + "Client has sended - " + str;

            nextBlockSize = 0;
            qDebug() << "TcpServer: Recieved " + str;

        }

}

//void tcpServer::disconnnectFromServer()
//{
    /*QTcpSocket *socket;
    socket = (QTcpSocket*)sender();
    for (auto peer:peerL->list){
        if (peer->getPeerSocket() == socket){
            peer->getPeerSocket()->close();
            peerL->list.removeOne(peer);
        }
    }
}*/

/*void tcpServer::slotSendToGraphics(QTcpSocket *sock, const QString &str)
{
    QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_2);
        out << quint16(0) << QTime::currentTime() << str;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        sock->write(arrBlock);

}*/
