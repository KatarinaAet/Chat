#include "graphics.h"


Graphics::Graphics(PeerList *listP, QWidget *parent) : QWidget(parent)
{
    this->peerL = listP;
    timer = new QTimer(this);
        /*!
         * каждые 5с будет отправляться заданное сообщение
         */
    connect(timer, SIGNAL(timeout()), this, SLOT(sendMes()));
    timer->start(5*1000);

    lay = new QVBoxLayout(this);

    qSplit1 = new QSplitter(Qt::Horizontal, this);
    qSplit2 = new QSplitter(Qt::Vertical, this);
    qSplit3 = new QSplitter(Qt::Vertical, this);
    chatField = new QTextEdit(this);
    chatField->setReadOnly(true);
    clientListField = new QTextEdit(this);
    //clientListField->setReadOnly(true);
    enterMesField = new QTextEdit(this);
    buttonSend = new QPushButton("Send", this);
    lay->addWidget(qSplit2);
    qSplit2->addWidget(qSplit1);
    qSplit1->addWidget(chatField);
    qSplit1->addWidget(clientListField);
    qSplit2->addWidget(qSplit3);
    qSplit3->addWidget(enterMesField);
    qSplit1->setSizes(QList<int>()<<200<<100);
    qSplit2->setSizes(QList<int>()<<300<<100);
    buttonSend->setFixedSize(50,20);
    lay->addWidget(buttonSend);

    connect(peerL, SIGNAL(newPeer(QString)), this, SLOT(slotNewPeer(QString)));
    //connect(peerL, SIGNAL(removePeer(QString)), this, SLOT(slotRemovePeer(QString)));

}

void Graphics::slotReceiveMessage(QString mes){

    qDebug()<<"Graphics:recieve___________"<<mes;
}

void Graphics::slotLog(QString log){
    qDebug()<<"Graphics:log___________"<<log;

}

void Graphics::sendMes(){


    emit signalSendToClient("Daniil","VILLYWONKA","from Ekaterina");
}

void Graphics::slotNewPeer(const QString &name)
{
    //QTextCursor curs = clientListField->textCursor();
    //curs.movePosition(QTextCursor::Start);
    //curs.insertText("aaa");

    QLabel *label= new QLabel(name,this);
    labelList.append(label);
    lay->addWidget(label);
    label->show();
    //QPushButton *label = new QPushButton(name);
    //lay->addWidget(label);
    //label->show();
    //label->setText(name);
    //qSplit1->addWidget(label);
    qDebug() << "I'M IN SLOT";
    qDebug() << "Graphics: " << name;
    //label->show();

}


