#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QHostInfo>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
    QString interfaceType(QNetworkInterface::InterfaceType type);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGetHostInfo_clicked();

    void do_lookUpHostInfo(const QHostInfo &host);

    void on_btnLookUp_clicked();

    void on_btnAllInterface_clicked();

    void on_btnAllAddress_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
