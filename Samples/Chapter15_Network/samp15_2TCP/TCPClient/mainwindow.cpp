#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostInfo>

// 获取本机IPv4地址
QString MainWindow::getLocalIP()
{
    QString hostName = QHostInfo::localHostName(); // 本机主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress> addrList = hostInfo.addresses(); // 本机IP地址列表
    if(addrList.isEmpty())
        return localIP;
    foreach (QHostAddress aHost, addrList) {
        if(QAbstractSocket::IPv4Protocol == aHost.protocol()){
            localIP = aHost.toString();
            break;
        }
    }
    return localIP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket(this); // 创建socket变量
    labSocketState = new QLabel("socket状态："); // 状态栏标签
    labSocketState->setMinimumWidth(250);
    ui->statusbar->addWidget(labSocketState);
    QString localIP = getLocalIP(); // 获取本机IP地址
    this->setWindowTitle(this->windowTitle() + "----本机IP地址：" + localIP);
    ui->comboBox->addItem(localIP);
    connect(tcpClient, SIGNAL(connected), this, SLOT(do_connected()));
    connect(tcpClient, SIGNAL(disconnected), this, SLOT(do_disconnected()));
    connect(tcpClient, &QTcpSocket::stateChanged, this, &MainWindow::do_socketStateChange);
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(do_socketReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_connected()
{// connected()信号的槽函数
    ui->plainTextEdit->appendPlainText("**已连接到服务器");
    ui->plainTextEdit->appendPlainText("**peer address:" + tcpClient->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" + QString::number(tcpClient->peerPort()));
    ui->actConnect->setEnabled(false);
    ui->actDisconnect->setEnabled(true);
}

void MainWindow::do_disconnected()
{// disconnected()信号的槽函数
    ui->plainTextEdit->appendPlainText("**已断开与服务器的连接");
    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
}

// 连接服务器按钮
void MainWindow::on_actConnect_triggered()
{
    QString addr = ui->comboBox->currentText();
    quint16 port = ui->spinBox->value();
    tcpClient->connectToHost(addr, port);
}


// 断开连接按钮
void MainWindow::on_actDisconnect_triggered()
{
    if(tcpClient->state() == QAbstractSocket::ConnectedState)
        tcpClient->disconnectFromHost();
}

void MainWindow::do_socketStateChange(QAbstractSocket::SocketState socketState)
{// socket状态变化时
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        labSocketState->setText("socket状态：UnconnectedState"); break;
    case QAbstractSocket::HostLookupState:
        labSocketState->setText("socket状态：HostLookupState"); break;
    case QAbstractSocket::ConnectingState:
        labSocketState->setText("socket状态：ConnectingState"); break;
    case QAbstractSocket::ConnectedState:
        labSocketState->setText("socket状态：ConnectedState"); break;
    case QAbstractSocket::BoundState:
        labSocketState->setText("socket状态：BoundState"); break;
    case QAbstractSocket::ClosingState:
        labSocketState->setText("socket状态：ClosingState"); break;
    case QAbstractSocket::ListeningState:
        labSocketState->setText("socket状态：ListeningState"); break;
    }
}


// 发送消息按钮
void MainWindow::on_pushButton_clicked()
{
    QString msg = ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    QByteArray str = msg.toUtf8();
    str.append('\n');
    tcpClient->write(str);
}

void MainWindow::do_socketReadyRead()
{// readyread()信号的槽函数
    while(tcpClient->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] " + tcpClient->readLine());
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

