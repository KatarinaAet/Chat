#-------------------------------------------------
#
# Project created by QtCreator 2018-08-20T11:32:12
#
#-------------------------------------------------

QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = SpoChat
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    udpclient.cpp \
    udpserver.cpp \
    idgenerator.cpp \
    peerlist.cpp \
    peertag.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    graphics.cpp \
    clickableqlabel.cpp


HEADERS  += mainwindow.h \
    udpclient.h \
    udpserver.h \
    idgenerator.h \
    peerlist.h \
    peertag.h \
    tcpserver.h \
    tcpclient.h \
    graphics.h \
    clickableqlabel.h

FORMS    += mainwindow.ui

CONFIG += c++11

SUBDIRS+= SpoChatTest
