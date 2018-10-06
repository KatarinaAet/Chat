#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T13:11:41
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = tst_spochattesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_spochattesttest.cpp \
/home/ekaterina/documents/Projects/Chat/SpoChat/clientlist.cpp \
/home/ekaterina/documents/Projects/Chat/SpoChat/clienttag.cpp \
/home/ekaterina/documents/Projects/Chat/SpoChat/udpclient.cpp \
/home/ekaterina/documents/Projects/Chat/SpoChat/udpserver.cpp \
/home/ekaterina/documents/Projects/Chat/SpoChat/idgenerator.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += /home/ekaterina/documents/Projects/Chat/SpoChat/clientlist.h \
/home/ekaterina/documents/Projects/Chat/SpoChat/clienttag.h \
/home/ekaterina/documents/Projects/Chat/SpoChat/udpclient.h \
/home/ekaterina/documents/Projects/Chat/SpoChat/udpserver.h \
/home/ekaterina/documents/Projects/Chat/SpoChat/idgenerator.h \

CONFIG += c++11
