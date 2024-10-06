#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QNetworkAccessManager networkManager; // 网络管理
    QNetworkReply *reply; // 网络响应
    QFile *downloadFile; // 下载保存临时文件

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_finished();
    void do_readyRead();
    void do_downloadProgress(qint64 bytesRead, qint64 totalBytes);

    void on_btnDefaultPath_clicked();

    void on_btnDownload_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
