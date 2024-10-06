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
    QString localIP = getLocalIP();
    this->setWindowTitle(this->windowTitle() + "----本机IP地址：" + localIP);
    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    connect(udpSocket, &QUdpSocket::stateChanged, this, &MainWindow::do_socketStateChange);
    do_socketStateChange(udpSocket->state()); // 立即刷新一次
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

MainWindow::~MainWindow()
{
    delete ui;
}

// 加入组播按钮
void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText();
    groupAddress = QHostAddress(IP); // 多播组地址
    quint16 groupPort = ui->spinPort->value(); // 端口
    if(udpSocket->bind(QHostAddress::AnyIPv4, groupPort, QUdpSocket::ShareAddress))
    {
        udpSocket->joinMulticastGroup(groupAddress); // 加入组播
        ui->textEdit->appendPlainText("**加入组播成功");
        ui->textEdit->appendPlainText("**组播IP地址：" + IP);
        ui->textEdit->appendPlainText("**绑定端口：" + QString::number(groupPort));
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
        ui->comboIP->setEnabled(false); // 组播地址和端口不能再修改
        ui->spinPort->setEnabled(false);
        ui->btnMulticast->setEnabled(true); // 发送消息的按钮可用
    }
    else
        ui->textEdit->appendPlainText("**绑定端口失败");
}


// 退出组播按钮
void MainWindow::on_actStop_triggered()
{
    udpSocket->leaveMulticastGroup(groupAddress); // 退出组播
    udpSocket->abort(); // 解除绑定
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->comboIP->setEnabled(true); // 组播地址和端口可以修改
    ui->spinPort->setEnabled(true);
    ui->btnMulticast->setEnabled(false); // 发送消息的按钮不可用
    ui->textEdit->appendPlainText("**已退出组播，解除端口绑定");
}


// 读取数据报
void MainWindow::do_socketReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &peerAddr, &peerPort);
        QString str = datagram.data();
        QString peer = "[From "+peerAddr.toString() + ":" + QString::number(peerPort) + "]";
        ui->textEdit->appendPlainText(peer + str);
    }
}

// 组播消息按钮， 发送组播消息
void MainWindow::on_btnMulticast_clicked()
{
    quint16 groupPort = ui->spinPort->value(); // 组播端口
    QString msg = ui->lineEdit->text();
    QByteArray datagram = msg.toUtf8();
    udpSocket->writeDatagram(datagram, groupAddress, groupPort);
    ui->textEdit->appendPlainText("[multicast]" + msg);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
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
    ui->textEdit->clear();
}

