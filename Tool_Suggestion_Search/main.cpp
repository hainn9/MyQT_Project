#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include<QObject>
#include <mainwindow.h>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    MainWindow w;
  // mainwindow list;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("listv",&w);
   // engine.rootContext()->setContextProperty("string"," ");
    QObject::connect(&app, SIGNAL(applicationStateChanged(Qt::ApplicationState)), &w, SLOT(onApplicationStateChanged(Qt::ApplicationState)));
    QObject::connect(&app, SIGNAL(applicationStateChanged(Qt::ApplicationState)), &w, SLOT(onApplicationStateChanged(Qt::ApplicationState)));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    auto& ctx = *engine.rootContext();

    int id = QFontDatabase::addApplicationFont(":/font/ms_pgothic.ttf");
    QString familyFont = QFontDatabase::applicationFontFamilies(id).at(0);
    ctx.setContextProperty("fontGothic", familyFont);
    w.initData(&engine);
    return app.exec();
}
