# QT Modules
QT += qml quick

# Target
TARGET = camera
TEMPLATE = app

# Extra Configs
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Sources and Headers
SOURCES += main.cpp \
    camera_texture.cpp \
    yuv2rgb_material.cpp \
    camera_player.cpp \
    imagestream.cpp \
    camera.cpp

HEADERS += \
    camera_texture.h \
    yuv2rgb_material.h \
    camera_player.h \
    imagestream.h \
    camera.h

DEFINES += "CONFIG_PC_PLATFORM"
SOURCES += pc_camera.cpp
HEADERS += pc_camera.h

# Qml Files
OTHER_FILES += main.qml

# Resources
RESOURCES += qml.qrc
QMAKE_RESOURCE_FLAGS += -no-compress

target.path = /opt/HuaTai
INSTALLS += target

# Objects Pathes
DESTDIR = bin
UI_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build
