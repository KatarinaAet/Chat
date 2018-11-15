#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "peerlist.h"
#include <QTime>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(PeerList* peerList,QObject *parent = 0);
    QTcpServer *tcpServer;
    quint16 nextBlockSize;
    PeerList *peerList;
signals:
    void signalSendToLog(QString messLog);//посылка системных сообщений в графику
    void signalSendToGraphics(QString mess);//посылка отправляемого сообщения в графику
public slots:
    void slotNewConnection();

    void slotConnected();
    void slotReadMessage();
    void slotError(QAbstractSocket::SocketError);
    void slotDisconnected();
    //void slotSendToGraphics(const QString nickName, const QString groupName, const QString message);

};

#endif // TCPSERVER_H

