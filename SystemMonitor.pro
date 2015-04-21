#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T16:22:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SystemMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filesystemsinfo.cpp \
    systeminfo.cpp

HEADERS  += mainwindow.h \
    filesystemsinfo.h \
    systeminfo.h \
    structures.h

FORMS    += mainwindow.ui
