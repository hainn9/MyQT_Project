#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "svgimage.h"
#include <QQuickView>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<SvgImage>("SVG", 1, 0, "SvgImage");
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQuickView viewer;
    viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    viewer.show();

    return app.exec();
}

