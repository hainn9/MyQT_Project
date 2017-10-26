#ifndef SERVER
#define SERVER

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include "qtquick2applicationviewer.h"
#include <QtDeclarative/QDeclarativePropertyMap>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();
    void initPropertyMap();
    void mapToQmlContext(const QString& strQmlObjName, QObject* objQt);
    void mapToQmlContext(const QString& strQmlObjName, QVariant objQt);
    void setQmlViewObject(QtQuick2ApplicationViewer* pRootObject);
    void updatePropertyMap(QString propName, QVariant propValue);
public slots:
    void accept();
    void readSocket();
private:
    QTcpServer m_tcpServer;
    QMutex m_mutex;
    QtQuick2ApplicationViewer* m_pQmlViewObject;
    QQmlContext *m_pRootContext;
    QDeclarativePropertyMap *m_pPropertyMap;
    int m_speed;
};

#endif // SERVER

