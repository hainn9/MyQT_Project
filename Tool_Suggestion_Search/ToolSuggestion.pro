TEMPLATE = app

QT += qml quick
QT += sql
CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainwindow.h

DISTFILES += \
    android_source/AndroidManifest.xml


#win32: LIBS += -L$$PWD/../../../../Tools/mysql-connector-c-6.1.6-win32/mysql-connector-c-6.1.6-win32/lib/ -llibmysql

#INCLUDEPATH += $$PWD/../../../../Tools/mysql-connector-c-6.1.6-win32/mysql-connector-c-6.1.6-win32/include
#DEPENDPATH += $$PWD/../../../../Tools/mysql-connector-c-6.1.6-win32/mysql-connector-c-6.1.6-win32/include

win32: LIBS += -L$$PWD/../../../../../../TestQT/mysql_connector/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../../../../../TestQT/mysql_connector/include
DEPENDPATH += $$PWD/../../../../../../TestQT/mysql_connector/include
