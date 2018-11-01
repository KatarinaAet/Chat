#include "tcpserver.h"

tcpServer::tcpServer(QObject *parent):QObject (parent)
{
    tcpServ = new QTcpServer(this);
    QTcpSocket *socket = new QTcpSocket(this);
    if (tcpServ->listen(QHostAddress::Any,4540)){
        connect(socket, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
        sockList.append(socket);
    }
    else{
        qDebug() << "Unable to listen " + tcpServ->errorString();
        tcpServ->close();
        return;
    }
}

void tcpServer::slotNewConnection()
{
    QTcpSocket *socket = new QTcpSocket(this);
    connect (socket, SIGNAL(readyRead()), this, SLOT(slotReadMessage()));
    connect (socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    sockList.append(socket);
    qDebug() << "tcpServer: Connected!";

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

void tcpServer::slotSendToGraphics(QTcpSocket *sock, const QString &str)
{
    QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_2);
        out << quint16(0) << QTime::currentTime() << str;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        sock->write(arrBlock);

}
