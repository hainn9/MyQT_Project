#ifndef HOTPLUGWATCHER_H
#define HOTPLUGWATCHER_H

#include <QObject>
#include <QThread>
#include "qdevicewatcher.h"

#ifndef __GNUC__
#define __PRETTY_FUNCTION__  __FUNCTION__
#endif

class HotplugWatcher : public QThread
{
    Q_OBJECT
public:
    HotplugWatcher(QObject *parent = 0):QThread(parent) {
        qDebug("ThreadID=%#x %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__);
        start();

        moveToThread(this); //Let bool event(QEvent *e) be in another thread
        watcher = new QDeviceWatcher;
        watcher->moveToThread(this);
        watcher->appendEventReceiver(this);
        connect(watcher, SIGNAL(deviceAdded(QString)), this, SLOT(slotDeviceAdded(QString)), Qt::DirectConnection);
        connect(watcher, SIGNAL(deviceChanged(QString)), this, SLOT(slotDeviceChanged(QString)), Qt::DirectConnection);
        connect(watcher, SIGNAL(deviceRemoved(QString)), this, SLOT(slotDeviceRemoved(QString)), Qt::DirectConnection);
        watcher->start();
    }

public slots:
    void slotDeviceAdded(const QString& dev) { qDebug("ThreadID=%#x %s: add %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
    void slotDeviceRemoved(const QString& dev) { qDebug("ThreadID=%#x %s: remove %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
    void slotDeviceChanged(const QString& dev) { qDebug("ThreadID=%#x %s: change %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
protected:
    virtual bool event(QEvent *e) {
        if (e->type() == QDeviceChangeEvent::registeredType()) {
            QDeviceChangeEvent *event = (QDeviceChangeEvent*)e;
            QString action("Change");
            if (event->action() == QDeviceChangeEvent::Add)
                action = "Add";
            else if (event->action() == QDeviceChangeEvent::Remove)
                action = "Remove";

            qDebug("ThreadID=%#x event=%d %s: %s %s", (quintptr)QThread::currentThreadId(), e->type(), __PRETTY_FUNCTION__, qPrintable(action), qPrintable(event->device()));
            event->accept();
            return true;
        }
        return QObject::event(e);
    }

private:
    QDeviceWatcher *watcher;
};

#endif // HOTPLUGWATCHER_H
