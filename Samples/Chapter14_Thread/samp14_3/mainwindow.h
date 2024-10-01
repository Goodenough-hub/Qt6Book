#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tdicethread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TDiceThread *threadA; // producer
    TValueThread *threadValue; // consumer1
    TPictureThread *threadPic; // consumer2

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_threadA_started();

    void do_threadA_finished();

    void do_newValue(int seq, int diceValue); // 与threadValue的newValue()信号连接

    void do_newPicture(QString picName); // 与threadPic的newPicture()信号连接

    void on_actThread_Run_triggered();

    void on_actThread_Quit_triggered();

    void on_actClear_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
