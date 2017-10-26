QT       += core gui quick opengl qml widgets
CONFIG      += C++11

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#lessThan(QT_MAJOR_VERSION, 5): error(This project requires Qt 5 or later)

TARGET = Display3DModel
TEMPLATE = app

#copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
#first.depends = $(first) copydata
#QMAKE_EXTRA_TARGETS += first copydata


SOURCES += main.cpp\
    modelloader.cpp \
    fboinsgrenderer.cpp \
    modelrenderer.cpp

HEADERS  += \
    modelloader.h \
    fboinsgrenderer.h \
    modelrenderer.h

copydata.commands = $(COPY_DIR) $$PWD/object $$OUT_PWD
first.depends = $(first) copydata
QMAKE_EXTRA_TARGETS += first copydata

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/assimp/ -lAssimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/assimp/ -lAssimp
else:unix: LIBS += -L$$PWD/assimp/ -lAssimp

INCLUDEPATH += $$PWD/assimp/include
DEPENDPATH += $$PWD/assimp/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/assimp/libAssimp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/assimp/libAssimp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/assimp/Assimp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/assimp/Assimp.lib
else:unix: PRE_TARGETDEPS += $$PWD/assimp/libAssimp.a

#unix: !macx {
#    INCLUDEPATH +=  /usr/include
#    LIBS += /usr/lib/libassimp.so
#}

#macx {
#    INCLUDEPATH +=  /usr/local/include
#    LIBS += /usr/local/lib/libassimp.dylib
#}

#win32 {
#    INCLUDEPATH += "C:/Assimp3/include"
#    LIBS += -L"C:/Assimp3/lib/Release" -lassimp
#}

#OTHER_FILES += ads_fragment.vert ads_fragment.frag \
#    es_ads_fragment.frag \
#    es_ads_fragment.vert

RESOURCES += \
#    resources.qrc \
    qml.qrc \
    object.qrc
