#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 下载进度
void MainWindow::do_downloadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

// 网络相应结束
void MainWindow::do_finished()
{
    QFileInfo fileInfo(downloadFile->fileName()); // 获取下载的文件的文件名
    downloadFile->close();
    delete downloadFile; // 删除临时文件对象
    reply->deleteLater(); // 由主事件循环删除此对象
    if(ui->checkBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    ui->btnDownload->setEnabled(true);
}

// 读取下载的数据
void MainWindow::do_readyRead()
{
    downloadFile->write(reply->readAll());
}

// 默认路径
void MainWindow::on_btnDefaultPath_clicked()
{
    QString curPath = QDir::currentPath();
    QDir dir(curPath);
    QString sub = "temp";
    dir.mkdir(sub);
    ui->editPath->setText(curPath + "/" + sub + "/");
}


// 下载按钮，开始下载
void MainWindow::on_btnDownload_clicked()
{
    QString urlSpec = ui->editURL->text().trimmed();
    if(urlSpec.isEmpty())
    {
        QMessageBox::information(this, "错误", "请指定需要下载的URL");
        return;
    }
    QUrl newUrl = QUrl::fromUserInput(urlSpec); // URL
    if(!newUrl.isValid())
    {
        QString info = "无效URL:" + urlSpec + "\n错误信息：" + newUrl.errorString();
        QMessageBox::information(this, "错误", info);
        return;
    }
    QString tempDir = ui->editPath->text().trimmed(); // 临时目录
    if(tempDir.isEmpty())
    {
        QMessageBox::information(this, "错误", "请指定保存下载文件的目录");
        return;
    }
    QString fullFileName = tempDir + newUrl.fileName(); // 文件名
    if(QFile::exists(fullFileName))
        QFile::remove(fullFileName);
    downloadFile = new QFile(fullFileName); // 创建临时文件
    if(!downloadFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "错误", "临时文件打开错误");
        return;
    }
    ui->btnDownload->setEnabled(false);
    // 发送网络请求，创建网络响应
    reply = networkManager.get(QNetworkRequest(newUrl));
    connect(reply, SIGNAL(readyRead()), this, SLOT(do_readyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(do_downloadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(do_finished()));
}

