#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::MainWindow)
    , speed(0)
{
//    timer = new QTimer;
//    timer->start(10000);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateSpeed()));
    m_ui->setupUi(this);

    connect(m_ui->buttonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(m_ui->pushButton, SIGNAL(clicked()), this, SLOT(send()));
}

MainWindow::~MainWindow()
{
    if(m_socket.isOpen())
        m_socket.close();

    delete m_ui;
}

void MainWindow::connectToServer()
{
    QString serverAddress = m_ui->lineEditAddress->text();
    int serverPort = 12345;
    if(serverAddress.isEmpty())
    {
        qDebug()<<"Server IP incorrect";
        return;
    }

    m_socket.connectToHost(serverAddress, serverPort, QTcpSocket::WriteOnly);
    bool isConnected = m_socket.waitForConnected(5000);
    if(!isConnected)
    {
        qDebug()<<"Cannot connect to server";
        return;
    }
    else {
        qDebug()<<"Connect to server success";
    }

    disconnect(m_ui->buttonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(m_ui->buttonConnect, SIGNAL(clicked()), this, SLOT(disconnectFromServer()));
    m_ui->buttonConnect->setText("Disconnect");
    enableEdit(false);
}

void MainWindow::disconnectFromServer()
{
    if(m_socket.error() == QTcpSocket::ConnectionRefusedError)
        qDebug()<<"Server was closed unexpectedly";

    m_socket.disconnectFromHost();

    disconnect(m_ui->buttonConnect, SIGNAL(clicked()), this, SLOT(disconnectFromServer()));
    connect(m_ui->buttonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    m_ui->buttonConnect->setText("Connect");
    enableEdit(true);
}

void MainWindow::send()
{
    QString data = m_ui->lineEditSpeed->text();
    m_socket.write(data.toStdString().c_str(), data.size());
    m_ui->lineEditSpeed->clear();
}

//void MainWindow::updateSpeed()
//{
//    speed = speed + 2;
//    qDebug()<<"value of speed sent:"<< speed;
//    if (speed > 200)
//        speed = 0;
//    QString str = QString::number(speed);
//    m_socket.write(str.toStdString().c_str(), str.size());
//}

void MainWindow::enableEdit(bool enable)
{
    m_ui->lineEditAddress->setEnabled(enable);
    m_ui->pushButton->setEnabled(!enable);
}
