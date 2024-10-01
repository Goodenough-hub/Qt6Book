#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event) // 确保在窗口关闭时线程被停止
{
    if(threadA->isRunning())
    {
        threadA->terminate(); // 强制终止线程
        threadA->wait(); // 等待线程结束
    }
    event->accept();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadA = new TDiceThread(this);
    connect(threadA, &TDiceThread::started, this, &MainWindow::do_threadA_started);
    connect(threadA, &TDiceThread::finished, this, &MainWindow::do_threadA_finished);
    connect(threadA, &TDiceThread::newValue, this, &MainWindow::do_threadA_newValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_threadA_started()
{// 与线程的 started() 信号关联
    ui->statusBar->showMessage("Thread状态：thread started");
    ui->actThread_Run->setEnabled(false); // “启动线程”按钮
    ui->actThread_Quit->setEnabled(true); // “结束线程”按钮
    ui->actDice_Run->setEnabled(true); // “开始”按钮
}

void MainWindow::do_threadA_finished()
{// 与线程的 finished() 信号关联
    ui->statusBar->showMessage("Thread状态：thread finished");
    ui->actThread_Run->setEnabled(true);
    ui->actThread_Quit->setEnabled(false);
    ui->actDice_Run->setEnabled(false); // “开始”按钮
    ui->actDice_Pause->setEnabled(false); // “暂停”按钮
}

void MainWindow::do_threadA_newValue(int seq, int diceValue)
{// 与线程的 newValue() 信号关联
    QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d", seq, diceValue);
    ui->plainTextEdit->appendPlainText(str);
    QString filename = QString::asprintf(":/icons/images/d%d.jpg", diceValue);
    QPixmap pic(filename); // 加载图片
    ui->labPic->setPixmap(pic); // 显示骰子图片
}

void MainWindow::on_actThread_Run_triggered()
{// “启动线程”按钮
    threadA->start();
}


void MainWindow::on_actThread_Quit_triggered()
{// “结束线程”按钮
    threadA->stopThread();
}


void MainWindow::on_actDice_Run_triggered()
{// “开始”按钮，开始掷骰子
    threadA->diceBegin();
    ui->actDice_Run->setEnabled(false);
    ui->actDice_Pause->setEnabled(true);
}


void MainWindow::on_actDice_Pause_triggered()
{// “暂停”按钮，暂停掷骰子
    threadA->dicePause();
    ui->actDice_Run->setEnabled(true);
    ui->actDice_Pause->setEnabled(false);
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

