#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T14:51:48
#
#-------------------------------------------------

QT += core gui network declarative
QT += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app
#include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
#qtcAddDeployment()

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
#    client.h

FORMS    += mainwindow.ui

#OTHER_FILES += \
#    qml/main.qml \

#DISTFILES += \
#    qml/main.qml
