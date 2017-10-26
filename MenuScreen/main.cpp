#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickView>
#include <QDebug>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    QQuickView viewer;
//    QObject::connect(viewer.engine(), SIGNAL(quit()), &viewer, SLOT(close()));
//    QQmlComponent component(viewer.engine(), QUrl(QStringLiteral("qrc:/data/listApp.qml")));
//    QObject *dummyData = component.create();
//    if (component.isError()) {
//        qDebug()<<"Load dummy data error";
//    }

//    if (dummyData) {
//        qDebug()<<"load done";
//        viewer.engine()->rootContext()->setContextProperty("listApp", dummyData);
//        dummyData->setParent(&viewer);
//    }
//    viewer.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    viewer.show();
    return app.exec();
}

