#include "server.h"
#include <QQmlContext>
#include "defines.h"

MyServer::MyServer(QObject *parent)
    : QObject(parent)
{
    m_pPropertyMap = new QDeclarativePropertyMap();
    m_pRootContext = NULL;
    m_pQmlViewObject = NULL;
    unsigned int portNumber = 12345;
    if (!m_tcpServer.listen(QHostAddress::Any, portNumber))
    {
        qDebug()<<"Start server fail";
        return;
    }
    else
    {
        qDebug()<<"Start server success";
    }
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(accept()));
}

MyServer::~MyServer()
{
    m_pPropertyMap->deleteLater();
    m_pQmlViewObject = NULL;
    m_pRootContext = NULL;
    if (!m_tcpServer.isListening())
        return;
    m_tcpServer.close();
}

void MyServer::initPropertyMap()
{
    mapToQmlContext(QT_PROPERTY_MAPPER, m_pPropertyMap);
    updatePropertyMap(QML_SPEED_VALUE, QVariant(0));
}

void MyServer::mapToQmlContext(const QString &strQmlObjName, QObject *objQt)
{
    if (m_pRootContext == NULL)
        return;
    m_pRootContext->setContextProperty(strQmlObjName, objQt);
}

void MyServer::mapToQmlContext(const QString &strQmlObjName, QVariant objQt)
{
    if (m_pRootContext == NULL)
        return;
    m_pRootContext->setContextProperty(strQmlObjName, objQt);
}

void MyServer::setQmlViewObject(QtQuick2ApplicationViewer *pRootObject)
{
    m_pQmlViewObject = pRootObject;
    m_pRootContext = m_pQmlViewObject->rootContext();
}

void MyServer::updatePropertyMap(QString propName, QVariant propValue)
{
    m_pPropertyMap->insert(propName, propValue);
}

void MyServer::accept()
{
    QTcpSocket *socket = m_tcpServer.nextPendingConnection();
    if (!socket)
        return;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MyServer::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    QString data = socket->readAll();
    bool ok;
    QMutexLocker locker(&m_mutex);
    int speed = data.toInt(&ok, 10);
    qDebug()<<"value of speed received: "<<speed;
    updatePropertyMap(QML_SPEED_VALUE, QVariant(speed));
}

