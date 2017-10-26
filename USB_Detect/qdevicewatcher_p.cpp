#include "qdevicewatcher.h"
#include "qdevicewatcher_p.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string>
#include <ctype.h>
#include <QDebug>
#include <QCoreApplication>
#include <QSocketNotifier>
#include <QRegExp>

#define UEVENT_BUFFER_SIZE      2048

enum udev_monitor_netlink_group {
    UDEV_MONITOR_NONE,
    UDEV_MONITOR_KERNEL,
    UDEV_MONITOR_UDEV
};


QDeviceWatcherPrivate::QDeviceWatcherPrivate(QObject *parent)
    :QObject(parent)
{

}

QDeviceWatcherPrivate::~QDeviceWatcherPrivate() {
    stop();
    close(netlink_socket);
    netlink_socket = -1;
}

bool QDeviceWatcherPrivate::start() {
    if(!init())
        return false;
    socket_notifier->setEnabled(true);
    return true;
}

bool QDeviceWatcherPrivate::stop() {
    if (netlink_socket != -1) {
        socket_notifier->setEnabled(false);
        close(netlink_socket);
        netlink_socket = -1;
    }
    return true;
}

bool QDeviceWatcherPrivate::init() {
    struct sockaddr_nl snl;
    const int buffersize = 16 * 124 *1024;
    int retval;

    memset(&snl, 0x00, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_groups = UDEV_MONITOR_KERNEL;

    netlink_socket = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (netlink_socket == -1) {
        qWarning("error getting socket: %s", strerror(errno));
        return false;
    }
    setsockopt(netlink_socket, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
    retval = bind(netlink_socket, (struct sockaddr*) &snl, sizeof(struct sockaddr_nl));
    if (retval < 0) {
        qWarning("bind failed: %s", strerror(errno));
        close(netlink_socket);
        netlink_socket = -1;
        return false;
    } else if (retval == 0) {
        struct sockaddr_nl _snl;
        socklen_t _addrlen = sizeof(struct sockaddr_nl);
        retval = getsockname(netlink_socket, (struct sockaddr *)&_snl, &_addrlen);
        if (retval == 0)
            snl.nl_pid = _snl.nl_pid;
    }
    socket_notifier = new QSocketNotifier(netlink_socket, QSocketNotifier::Read, this);
    connect(socket_notifier, SIGNAL(activated(int)), SLOT(parseDeviceInfo())); //will always active
    socket_notifier->setEnabled(false);
    return true;
}

void QDeviceWatcherPrivate::parseDeviceInfo() {
    QByteArray data;
    data.resize(UEVENT_BUFFER_SIZE*2);
    data.fill(0);
    size_t len = read(socket_notifier->socket(), data.data(), UEVENT_BUFFER_SIZE*2);
    qDebug("read fro socket %d bytes", len);
    data.resize(len);
    data = data.replace(0, '\n').trimmed();
    if (buffer.isOpen())
        buffer.close();
    buffer.setBuffer(&data);
    buffer.open(QIODevice::ReadOnly);
    while(!buffer.atEnd()) {
        parseLine(buffer.readLine().trimmed());
    }
    buffer.close();
}

void QDeviceWatcherPrivate::parseLine(const QByteArray &line) {
    qDebug("%s", line.constData());
    if (!line.contains("/block/"))
        return;
    QString action_str = line.left(line.indexOf('@')).toLower();
    QString dev = "/dev/" + line.right(line.length() - line.lastIndexOf('/') - 1);
    QDeviceChangeEvent *event = 0;

    if (action_str==QLatin1String("add")) {
        emitDeviceAdded(dev);
        event = new QDeviceChangeEvent(QDeviceChangeEvent::Add, dev);
    } else if (action_str==QLatin1String("remove")) {
        emitDeviceRemoved(dev);
        event = new QDeviceChangeEvent(QDeviceChangeEvent::Remove, dev);
    } else if (action_str==QLatin1String("change")) {
        emitDeviceChanged(dev);
        event = new QDeviceChangeEvent(QDeviceChangeEvent::Change, dev);
    }

    qDebug("%s %s", qPrintable(action_str), qPrintable(dev));

    if (event != 0 && !event_receivers.isEmpty()) {
        foreach(QObject* obj, event_receivers) {
            QCoreApplication::postEvent(obj, event, Qt::HighEventPriority);
        }
    }
}
