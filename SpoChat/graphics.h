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
#include "clickableqlabel.h"

class Graphics : public QWidget
{
    Q_OBJECT
public:
    explicit Graphics(PeerList *listP, QWidget *parent = 0);

private:
    QTextEdit *chatField;
    QTextEdit *enterMesField;
    QSplitter *qSplit1;
    QPushButton *buttonSend, *buttonClose;
    PeerList *peerL;
    QTimer *timer;
    QVBoxLayout *mesLay, *peerLay;
    QHBoxLayout *mainLay, *buttonLay;
    QList<ClickableQLabel*> labelList;


signals:
    void signalSendToClient(QString name,QString group,QString mess);
public slots:
    void slotReceiveMessage(QString mess);
    void slotLog(QString log);

    void sendMes();
    void slotNewPeer(const QString &name);
    void slotRemovePeer(const QString &name);
    void slotGiveMesField();
    void slotCloseWidgets();
};

#endif // GRAPHICS_H


