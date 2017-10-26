#ifndef CLIENT
#define CLIENT

#include <QQuickItem>
#include <QTcpSocket>
#include <QTimer>

class MyClient : public QQuickItem
{
    Q_OBJECT
public:
    explicit MyClient(QQuickItem *parent = 0);
    ~MyClient();

public slots:
    void connectToServer();
    void disconnectFromServer();
    void updateSpeed();
private:
    QTcpSocket m_socket;
    int speed;
    QTimer *timer;
};

#endif // CLIENT

