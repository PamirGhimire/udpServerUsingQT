#-------------------------------------------------
#
# Project created by QtCreator 2017-08-03T20:04:26
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = udpGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udpserver.cpp

HEADERS  += mainwindow.h \
    udpserver.h

FORMS    += mainwindow.ui
