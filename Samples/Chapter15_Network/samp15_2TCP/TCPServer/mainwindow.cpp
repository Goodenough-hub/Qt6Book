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
    labListen = new QLabel("监听状态：");
    labListen->setMinimumWidth(150);
    ui->statusbar->addWidget(labListen);
    labSocketState = new QLabel("socket状态：");
    labSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(labSocketState);

    QString localIP = getLocalIP(); // 获取本机IP地址
    this->setWindowTitle(this->windowTitle() + "----本机IP地址：" + localIP);
    ui->comboBox->addItem(localIP);
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(do_newConnection()));
}

// 确保窗口关闭时断开与TCP客户端的socket连接，停止TCP服务器的网络监听
MainWindow::~MainWindow()
{// 析构函数
    if(tcpSocket != nullptr)
    {
        if(tcpSocket->state() == QAbstractSocket::ConnectedState)
            tcpSocket->disconnectFromHost(); // 断开与客户端的连接
    }
    if(tcpServer->isListening())
        tcpServer->close(); // 停止网络监听
    delete ui;
}

void MainWindow::do_newConnection()
{
    tcpSocket = tcpServer->nextPendingConnection(); // 创建socket
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(do_clientConnected()));
    do_clientConnected(); // 运行一次槽函数，显示状态
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(do_clientDisconnected()));
    connect(tcpSocket, &QTcpSocket::stateChanged, this, &MainWindow::do_socketStateChange);
    do_socketStateChange(tcpSocket->state()); // 运行一次槽函数，显示状态
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(do_socketReadyRead()));
}



void MainWindow::do_clientConnected()
{// 客户端接入时
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address:" + tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" + QString::number(tcpSocket->peerPort()));
}

void MainWindow::do_clientDisconnected()
{// 客户端断开连接时
    ui->plainTextEdit->appendPlainText("**client socket disconnected");
    tcpSocket->deleteLater();
}

void MainWindow::do_socketReadyRead()
{// 读取缓冲区的行文本
    while(tcpSocket->canReadLine())
        ui->plainTextEdit->appendPlainText("[in] " + tcpSocket->readLine());
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

void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}


// 开始监听
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboBox->currentText(); // IP地址字符串，如"127.0.0.1"
    quint16 port = ui->spinBox->value(); // 端口
    QHostAddress address(IP); // 通过IP地址字符串创建QHostAddress对象
    tcpServer->listen(address, port); // 开始监听
    ui->plainTextEdit->appendPlainText("**开始监听...");
    ui->plainTextEdit->appendPlainText("**服务器地址："+tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**服务器端口：" + QString::number(tcpServer->serverPort()));
    ui->actStart->setEnabled(false);
    ui->actStop->setEnabled(true);
    labListen->setText("监听状态：正在监听");
}


// 停止监听
void MainWindow::on_actStop_triggered()
{
    if(tcpServer->isListening()) // tcpServer正在监听
    {
        if(tcpSocket != nullptr)
        {
            if(tcpSocket->state() == QAbstractSocket::ConnectedState)
                tcpSocket->disconnectFromHost();
        }
        tcpServer->close(); // 停止监听
        ui->actStart->setEnabled(true);
        ui->actStop->setEnabled(false);
        labListen->setText("监听状态：已停止监听");
    }
}


// 发送消息按钮——发送一行字符串，以换行符结束
void MainWindow::on_btnSend_clicked()
{
    QString msg = ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText("[out] " + msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
    QByteArray str = msg.toUtf8();
    str.append('\n'); // 添加一个换行符
    tcpSocket->write(str);
}

