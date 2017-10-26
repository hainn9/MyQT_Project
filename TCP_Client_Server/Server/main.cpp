#include "server.h"
#include <QGuiApplication>
#include "defines.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
    MyServer *server = new MyServer;
    server->setQmlViewObject(&viewer);
    server->initPropertyMap();

    viewer.setMainQmlFile(QStringLiteral("qml/main.qml"));
    viewer.setFlags(
                Qt::Window
            | 	Qt::MSWindowsFixedSizeDialogHint
            | 	Qt::FramelessWindowHint
            );
    viewer.show();

    return app.exec();
}
