#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMutex>

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
    void start();
    void stop();
    void accept();
    void readSocket();

//    void chooseSaveFile();

private:
    void enableEdit(bool enable);

private:
    Ui::MainWindow* m_ui;
    QTcpServer m_tcpServer;
    QMutex m_mutex;
};

#endif
