#include "graphics.h"


Graphics::Graphics(PeerList *listP, QWidget *parent) : QWidget(parent)
{
    this->peerL = listP;
    //timer = new QTimer(this);
        /*!
         * каждые 5с будет отправляться заданное сообщение
         */
    //connect(timer, SIGNAL(timeout()), this, SLOT(sendMes()));
    //timer->start(5*1000);

    mainLay = new QHBoxLayout(this);
    mesLay = new QVBoxLayout(this);
    peerLay = new QVBoxLayout(this);
    peerLay->setAlignment(Qt::AlignTop);

    qSplit1 = new QSplitter(Qt::Vertical, this);
    chatField = new QTextEdit(this);
    chatField->setReadOnly(true);
    enterMesField = new QTextEdit(this);
    buttonSend = new QPushButton("Send", this);
    buttonSend->setVisible(false);
    buttonClose = new QPushButton("Close", this);
    buttonClose->setVisible(false);
    qSplit1->setVisible(false);
    chatField->setVisible(false);
    enterMesField->setVisible(false);
    mainLay->addLayout(mesLay);
    mainLay->addLayout(peerLay);
    mainLay->setStretchFactor(mesLay,5);
    mainLay->setStretchFactor(peerLay, 5);

    connect(peerL, SIGNAL(newPeer(QString)), this, SLOT(slotNewPeer(QString)));
    connect(peerL, SIGNAL(removePeer(QString)), this, SLOT(slotRemovePeer(QString)));
    connect(buttonSend, SIGNAL(clicked(bool)), this, SLOT(sendMes()));
    connect(buttonClose, SIGNAL(clicked(bool)), this, SLOT(slotCloseWidgets()));

}

void Graphics::slotReceiveMessage(QString mes){
    qDebug() << "Message recieved";
    if (!chatField->isVisible()){
        slotGiveMesField();
        chatField->setText(mes);
    }
    else
        chatField->setText(mes);
}

void Graphics::slotLog(QString log){
    qDebug()<<"Graphics:log___________"<<log;

}

void Graphics::sendMes(){

    QString str = enterMesField->toPlainText();
    if (str.isEmpty())
        return;
    else{
    QStringList outputMessage = str.split("@");
    qDebug() << outputMessage[0]<< outputMessage[1] << outputMessage[2];
    emit signalSendToClient(outputMessage[0],outputMessage[1],outputMessage[2]);
    }
}

void Graphics::slotNewPeer(const QString &name)
{

    if (name.isEmpty())
        return;
    else{
        ClickableQLabel *label= new ClickableQLabel(name,this);
        labelList.append(label);
        peerLay->addWidget(label);
        connect(label, SIGNAL(clicked()), this, SLOT(slotGiveMesField()));
        qDebug() << "I'M IN SLOT";
        qDebug() << "Graphics: " << name;
    }


}

void Graphics::slotRemovePeer(const QString &name)
{
    qDebug() << "IN SLOT REMOVE " << name;
    if (!mainLay->isEmpty()){
        for (auto item:labelList){
            if (item->text() == name){
                qDebug() << "I FOUND IT";
                delete item;
                labelList.removeOne(item);
                slotCloseWidgets();
                return;
            }
        }
    }

}

void Graphics::slotGiveMesField()
{
    //qSplit1 = new QSplitter(Qt::Vertical, this);
    //chatField = new QTextEdit(this);
    //chatField->setReadOnly(true);
    //enterMesField = new QTextEdit(this);
    //buttonSend = new QPushButton("Send", this);
    buttonSend->setVisible(true);
    qSplit1->setVisible(true);
    chatField->setVisible(true);
    enterMesField->setVisible(true);
    buttonClose->setVisible(true);
    mesLay->addWidget(qSplit1);
    qSplit1->addWidget(chatField);
    qSplit1->addWidget(enterMesField);
    mesLay->addWidget(buttonSend);
    mesLay->addWidget(buttonClose);
    qSplit1->setSizes(QList<int>()<<200<<100);
    buttonSend->setFixedSize(50,20);
    buttonClose->setFixedSize(50,20);
}

void Graphics::slotCloseWidgets()
{
    buttonSend->setVisible(false);
    buttonClose->setVisible(false);
    qSplit1->setVisible(false);
    chatField->setVisible(false);
    enterMesField->setVisible(false);
}


