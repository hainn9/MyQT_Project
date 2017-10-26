#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QTimer>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void connectToServer();
    void disconnectFromServer();
//    void updateSpeed();
    void send();

private:
    void enableEdit(bool enable);

private:
    Ui::MainWindow* m_ui;
    QTcpSocket m_socket;
    int speed;
    QTimer *timer;
};

#endif
