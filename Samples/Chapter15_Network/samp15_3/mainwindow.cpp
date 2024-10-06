#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHostInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labSocketState = new QLabel("socket状态：");
    labSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(labSocketState);
    QString localIP = getLocalIP(); // 获取本机IP地址
    this->setWindowTitle(this->windowTitle() + "----本机IP地址："+localIP);
    ui->comboTargetIP->addItem(localIP);
    udpSocket = new QUdpSocket(this); // 创建socket

    connect(udpSocket, &QUdpSocket::stateChanged, this, &MainWindow::do_socketStateChange);
    do_socketStateChange(udpSocket->state()); // 运行一次，显示当前状态
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(do_socketReadyRead()));
}

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

// 读取收到的数据报
void MainWindow::do_socketReadyRead()
{
    while(udpSocket->hasPendingDatagrams()) // 是否有待读取的数据报
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize()); // 待读取的数据报的字节数
        QHostAddress peerAddr; // 对方地址
        quint16 peerPort; // 对方端口
        udpSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);
        QString str = datagram.data();
        QString peer = "[From " + peerAddr.toString() + ":" + QString::number(peerPort) + "] ";
        ui->textEdit->appendPlainText(peer+str);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 绑定端口按钮
void MainWindow::on_actStart_triggered()
{
    quint16 port = ui->spinBindPort->value(); // 本机UDP端口
    if(udpSocket->bind(port)) // 绑定端口成功
    {
        ui->textEdit->appendPlainText("**已成功绑定");
        ui->textEdit->appendPlainText("**绑定端口：" + QString::number(udpSocket->localPort()));
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
        ui->btnSend->setEnabled(true);
        ui->btnBroadcast->setEnabled(true);
    }
    else
        ui->textEdit->appendPlainText("**绑定失败");
}


// 解除绑定按钮
void MainWindow::on_actStop_triggered()
{
    udpSocket->abort(); // 解除绑定，复位socket
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->btnSend->setEnabled(false);
    ui->btnBroadcast->setEnabled(false);
    ui->textEdit->appendPlainText("**已解除绑定");
}


// 发送消息按钮
void MainWindow::on_btnSend_clicked()
{
    QString targetIP = ui->comboTargetIP->currentText(); // 目标IP地址
    QHostAddress targetAddr(targetIP); // 目标主机
    quint16 targetPort = ui->spinTargetPort->value(); // 目标端口
    QString msg = ui->lineEdit->text(); // 发送的消息内容
    QByteArray str = msg.toUtf8();
    udpSocket->writeDatagram(str, targetAddr, targetPort); // 发出数据报
    ui->textEdit->appendPlainText("[out] " + msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}


// 广播消息
void MainWindow::on_btnBroadcast_clicked()
{
    quint16 targetPort = ui->spinTargetPort->value(); // 目标端口
    QString msg = ui->lineEdit->text();
    QByteArray str = msg.toUtf8();
    udpSocket->writeDatagram(str, QHostAddress::Broadcast, targetPort);
    ui->textEdit->appendPlainText("[broadcast] " + msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

