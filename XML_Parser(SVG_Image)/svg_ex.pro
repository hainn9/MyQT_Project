TEMPLATE = app

QT += qml quick
QT += svg
QT += xml
CONFIG += c++11

SOURCES += main.cpp \
    svgimage.cpp

RESOURCES += qml.qrc \
    image.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    svgimage.h

