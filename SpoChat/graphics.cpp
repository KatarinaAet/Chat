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
    buttonLay = new QHBoxLayout(this);
    peerLay->setAlignment(Qt::AlignTop);
    chatField = new QTextEdit(this);
    chatField->setReadOnly(true);
    enterMesField = new QTextEdit(this);
    buttonSend = new QPushButton("Send", this);
    buttonSend->setVisible(false);
    buttonClose = new QPushButton("Close", this);
    buttonClose->setVisible(false);
    buttonSend->setFixedSize(100,40);
    buttonClose->setFixedSize(100,40);
    buttonLay->addWidget(buttonSend, Qt::AlignTop);
    buttonLay->addWidget(buttonClose, Qt::AlignTop);
    chatField->setVisible(false);
    enterMesField->setVisible(false);
    mesLay->addWidget(chatField);
    mesLay->addWidget(enterMesField);
    mesLay->addLayout(buttonLay);
    //mesLay->addWidget(buttonSend);
    //mesLay->addWidget(buttonClose);

    mesLay->setStretch(0,6);
    mesLay->setStretch(1,3);
    mainLay->addLayout(mesLay);
    mainLay->addLayout(peerLay);
    mainLay->setStretch(0,7);
    mainLay->setStretch(1,3);
    setLayout(mainLay);

    connect(peerL, SIGNAL(newPeer(QString)), this, SLOT(slotNewPeer(QString)));
    connect(peerL, SIGNAL(removePeer(QString)), this, SLOT(slotRemovePeer(QString)));
    connect(buttonSend, SIGNAL(clicked(bool)), this, SLOT(sendMes()));
    connect(buttonClose, SIGNAL(clicked(bool)), this, SLOT(slotCloseWidgets()));

}

void Graphics::slotReceiveMessage(QString mes){
    qDebug() << "Message recieved";
    QStringList outMes = mes.split("@");
    if (!chatField->isVisible()){
        slotGiveMesField();
        chatField->append(outMes[0]+":"+outMes[2]);
    }
    else
        chatField->append(outMes[0]+":"+outMes[2]);
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
    chatField->append(outputMessage[0]+":"+outputMessage[2]);
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
    buttonSend->setVisible(true);
    chatField->setVisible(true);
    enterMesField->setVisible(true);
    buttonClose->setVisible(true);

}

void Graphics::slotCloseWidgets()
{
    buttonSend->setVisible(false);
    buttonClose->setVisible(false);
    chatField->setVisible(false);
    enterMesField->setVisible(false);
}


