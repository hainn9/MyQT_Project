#include <QCoreApplication>
#include "hotplugwatcher.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HotplugWatcher hotplug;
    qDebug()<<"starting ...";

    return a.exec();
}
