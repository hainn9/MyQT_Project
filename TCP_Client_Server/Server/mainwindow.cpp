#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMutexLocker>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>


MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(&m_tcpServer, SIGNAL(newConnection()), this, SLOT(accept()));
}

MainWindow::~MainWindow()
{
    stop();
    delete m_ui;
}

void MainWindow::start()
{
    bool wasOk = false;
    unsigned int portNumber = m_ui->lineEditPort->text().toUInt(&wasOk);
    if(!wasOk)
    {
        qDebug()<<"Port number incorrect";
        return;
    }

    if(!m_tcpServer.listen(QHostAddress::Any, portNumber))
    {
        qDebug()<<"Start server fail";
        return;
    }

    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stop()));
    m_ui->buttonStart->setText("Stop");
    enableEdit(false);
}

void MainWindow::stop()
{
    if(!m_tcpServer.isListening())
        return;

    m_tcpServer.close();

    disconnect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(stop()));
    connect(m_ui->buttonStart, SIGNAL(clicked()), this, SLOT(start()));
    m_ui->buttonStart->setText("Start");
    enableEdit(true);
}

void MainWindow::accept()
{
    QTcpSocket* socket = m_tcpServer.nextPendingConnection();
    if(!socket)
        return;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MainWindow::readSocket()
{
    QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
    QString message = socket->readAll();
    bool ok;

    QMutexLocker locker(&m_mutex);
    int speed = message.toInt(&ok, 10);
    qDebug()<<"value of speed received: "<<speed;
}

void MainWindow::enableEdit(bool enable)
{
    m_ui->lineEditPort->setEnabled(enable);
}

