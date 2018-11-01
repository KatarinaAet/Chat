#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>

class tcpServer : public QObject
{
    Q_OBJECT
public:
    tcpServer(QObject *parent = 0);
    QTcpServer *tcpServ;
    QList <QTcpSocket*> sockList;
    quint16 nextBlockSize;
public slots:
    void slotNewConnection();
    void slotReadMessage();
    void slotSendToGraphics(QTcpSocket* sock, const QString &str);

};

#endif // TCPSERVER_H
