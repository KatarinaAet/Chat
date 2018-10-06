#-------------------------------------------------
#
# Project created by QtCreator 2018-08-20T11:32:12
#
#-------------------------------------------------

QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpoChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientlist.cpp \
    udpclient.cpp \
    udpserver.cpp \
    clienttag.cpp \
    idgenerator.cpp


HEADERS  += mainwindow.h \
    clientlist.h \
    udpclient.h \
    udpserver.h \
    clienttag.h \
    idgenerator.h

FORMS    += mainwindow.ui

CONFIG += c++11

SUBDIRS+= SpoChatTest
