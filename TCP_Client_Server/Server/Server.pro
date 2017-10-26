folder_01.source = qml
DEPLOYMENTFOLDERS = folder_01
QT += core gui network declarative
QT += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

SOURCES += main.cpp\
            server.cpp

HEADERS  += server.h \
    defines.h

OTHER_FILES += \
    qml/main.qml \

DISTFILES += \
    qml/main.qml

RESOURCES += \
    image.qrc
