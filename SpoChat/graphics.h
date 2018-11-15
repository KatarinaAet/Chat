#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QObject>
#include <QWidget>
#include <QDebug>

#include <QTextEdit>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QTimer>
#include "peerlist.h"
#include <QTextCursor>
#include <QLabel>

class Graphics : public QWidget
{
    Q_OBJECT
public:
    explicit Graphics(PeerList *listP, QWidget *parent = 0);
private:
    QTextEdit *chatField;
    QTextEdit *clientListField;
    QTextEdit *enterMesField;
    QSplitter *qSplit1, *qSplit2, *qSplit3;
    QPushButton *buttonSend;
    PeerList *peerL;
    QTimer *timer;
    QVBoxLayout *leftLay, *rightLay, *lay;
    QHBoxLayout *mainLay;

    QVBoxLayout *left, *right, *mainl;
    QList<QLabel*> labelList;


signals:
    void signalSendToClient(QString name,QString group,QString mess);
public slots:
    void slotReceiveMessage(QString mess);
    void slotLog(QString log);

    void sendMes();
    void slotNewPeer(const QString &name);
    //void textChange(const QString &text);
    //void slotRemovePeer(const QString &name);
};

#endif // GRAPHICS_H


