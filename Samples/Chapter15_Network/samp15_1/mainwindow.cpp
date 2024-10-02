#include "mainwindow.h"
#include "./ui_mainwindow.h"

// 通过协议类型返回协议名称字符串
QString MainWindow::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch(protocol)
    {
    case QAbstractSocket::IPv4Protocol:
        return "IPv4";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6";
    case QAbstractSocket::AnyIPProtocol:
        return "Any Internet Protocol";
    default:
        return "Unknow Network Layer Protocol";
    }
}

// 根据枚举值返回字符串
QString MainWindow::interfaceType(QNetworkInterface::InterfaceType type)
{
    switch(type)
    {
    case QNetworkInterface::Unknown:
        return "Unknown";
    case QNetworkInterface::Loopback:
        return "Loopback";
    case QNetworkInterface::Ethernet:
        return "Ethernet";
    case QNetworkInterface::Wifi:
        return "Wifi";
    default:
        return "Other type";
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置comboBox
    ui->comboBox->addItem("www.ptpress.com.cn");
    ui->comboBox->addItem("www.huawei.com");
    ui->comboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 获取本机主机名和IP地址
void MainWindow::on_btnGetHostInfo_clicked()
{
    ui->plainTextEdit->clear();
    QString hostName = QHostInfo::localHostName(); // 本机主机名
    ui->plainTextEdit->appendPlainText("本机主机名：" + hostName + "\n");
    QHostInfo hostInfo = QHostInfo::fromName(hostName); // 本机IP地址
    QList<QHostAddress> addrList = hostInfo.addresses(); // IP地址列表
    if(addrList.isEmpty())
        return;
    foreach (QHostAddress host, addrList) {
        bool show = ui->chkBox_OnlyIPv4->isChecked();
        show = show ? (host.protocol() == QAbstractSocket::IPv4Protocol): true;
        if(show)
        {
            ui->plainTextEdit->appendPlainText("协 议：" + protocolName(host.protocol())); // 协议
            ui->plainTextEdit->appendPlainText("本机IP地址：" + host.toString()); // IP地址
            ui->plainTextEdit->appendPlainText(QString("isGlobal() = %1\n").arg(host.isGlobal()));
        }
    }
}

// 查找主机信息的槽函数
void MainWindow::do_lookUpHostInfo(const QHostInfo &host)
{
    QList<QHostAddress> addrList = host.addresses(); // 获取主机的地址列表
    if(addrList.isEmpty())
        return;
    foreach (QHostAddress host, addrList) {
        bool show = ui->chkBox_OnlyIPv4->isChecked(); // 只显示IPv4
        show = show? (host.protocol() == QAbstractSocket::IPv4Protocol): true;
        if(show)
        {
            ui->plainTextEdit->appendPlainText("协 议：" + protocolName(host.protocol()));
            ui->plainTextEdit->appendPlainText(host.toString());
            ui->plainTextEdit->appendPlainText(QString("isGlobal() == %1\n").arg(host.isGlobal()));
        }
    }
}


// 查找域名的IP地址
void MainWindow::on_btnLookUp_clicked()
{
    ui->plainTextEdit->clear();
    QString hostname = ui->comboBox->currentText(); // 读取主机名
    ui->plainTextEdit->appendPlainText("正在查找主机信息：" + hostname);
    QHostInfo::lookupHost(hostname, this, SLOT(do_lookUpHostInfo(QHostInfo)));
}


// allInterfaces()按钮——获取所有网络接口列表
void MainWindow::on_btnAllInterface_clicked()
{
    ui->plainTextEdit->clear();
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); // 网络接口列表
    foreach (QNetworkInterface interface, list) {
        if(!interface.isValid())
            continue;
        ui->plainTextEdit->appendPlainText("设备名称：" + interface.humanReadableName());
        ui->plainTextEdit->appendPlainText(("硬件地址：" + interface.hardwareAddress()));
        ui->plainTextEdit->appendPlainText("接口类型：" + interfaceType(interface.type()));
        QList<QNetworkAddressEntry> entryList = interface.addressEntries(); // 地址列表
        foreach (QNetworkAddressEntry entry, entryList) {
            ui->plainTextEdit->appendPlainText("    IP地址：" + entry.ip().toString());
            ui->plainTextEdit->appendPlainText("    子网掩码：" + entry.netmask().toString());
            ui->plainTextEdit->appendPlainText("    广播地址：" + entry.broadcast().toString() + "\n");
        }
    }
}

// allAddresses()按钮
void MainWindow::on_btnAllAddress_clicked()
{
    ui->plainTextEdit->clear();
    QList<QHostAddress> addrList = QNetworkInterface::allAddresses(); // IP地址列表
    if(addrList.isEmpty())
        return;
    foreach (QHostAddress host, addrList)
    {
        bool show = ui->chkBox_OnlyIPv4->isChecked(); // 只显示IPv4
        show = show? (host.protocol() == QAbstractSocket::IPv4Protocol): true;
        if(show)
        {
            ui->plainTextEdit->appendPlainText("协 议" + protocolName(host.protocol()));
            ui->plainTextEdit->appendPlainText("IP地址：" + host.toString());
            ui->plainTextEdit->appendPlainText(QString("isGlobal() = %1\n").arg(host.isGlobal()));
        }
    }
}

