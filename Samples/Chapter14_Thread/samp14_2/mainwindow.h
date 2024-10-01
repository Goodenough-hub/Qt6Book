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
    TDiceThread *threadA;
    QTimer *timer; // 定时器
    int m_seq;
    int m_diceValue;

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_threadA_started();

    void do_threadA_finished();

    void do_threadA_newValue(int seq, int diceValue);

    void on_actThread_Run_triggered();

    void on_actThread_Quit_triggered();

    void on_actDice_Run_triggered();

    void on_actDice_Pause_triggered();

    void on_actClear_triggered();

    void do_timeOut(); // 定时器的槽函数

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
