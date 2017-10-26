#ifndef QDEVICEWATCHER_H
#define QDEVICEWATCHER_H

#include <QtCore/QObject>
#include <QtCore/QEvent>
#include "qdevicewatcher_p.h"
class QDeviceWatcherPrivate;

class QDeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QDeviceWatcher)
public:
    explicit QDeviceWatcher(QObject *parent = 0);
    ~QDeviceWatcher();

    bool start();
    bool stop();
    bool isRunning() const;

    void appendEventReceiver(QObject* receiver);

signals:
    void deviceAdded(const QString& dev);
    void deviceChanged(const QString& dev);
    void deviceRemoved(const QString& dev);

protected:
    bool running;
    QDeviceWatcherPrivate *d_ptr;
};


class QDeviceChangeEvent : public QEvent
{
public:
    enum Action { Add, Remove, Change};

    explicit QDeviceChangeEvent(Action action, const QString& device);

    Action action() const {return m_action;}
    QString device() const {return m_device;}
    static Type registeredType()
    {
        static Type EventType = static_cast<Type>(registerEventType());
        return EventType;
    }

private:
    Action m_action;
    QString m_device;
};

#endif // QDEVICEWATCHER_H
