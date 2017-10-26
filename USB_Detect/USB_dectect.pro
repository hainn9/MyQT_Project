#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T00:41:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = USB_dectect
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_p.cpp

HEADERS += \
    qdevicewatcher_p.h \
    qdevicewatcher.h \
    hotplugwatcher.h
