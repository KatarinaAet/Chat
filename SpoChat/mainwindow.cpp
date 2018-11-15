#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics.h"
#include "peerlist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PeerList *peer = new PeerList();
    Graphics* graphics = new Graphics(peer);
    setCentralWidget(graphics);
}

MainWindow::~MainWindow()
{
    delete ui;
}
