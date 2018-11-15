#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>
#include <peerlist.h>
#include <QTextStream>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(PeerList *listOfPeer,QObject *parent = 0);
    PeerList *peerList;
    quint16 nextBlockSize;


signals:
    void signalSendToLog(QString messLog);//посылка системных сообщений в графику
    void signalSendToGraphics(QString mess);//посылка отправляемого сообщения в графику
public slots:

    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError);
    void slotReadMessage();

    void slotSendTo(QString nickName, QString groupName, QString messageTo);//мы получили сигнал кому отослать сообщение и само сообщение из г.и.

};

#endif // TCPCLIENT_H
