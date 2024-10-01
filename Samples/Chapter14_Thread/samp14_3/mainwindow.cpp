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
    threadA = new TDiceThread(this); // producer
    threadValue = new TValueThread(this); // consumer1
    threadPic = new TPictureThread(this); // consumer2
    connect(threadA, &TDiceThread::started, this, &MainWindow::do_threadA_started);
    connect(threadA, &TDiceThread::finished, this, &MainWindow::do_threadA_finished);
    connect(threadValue, &TValueThread::newValue, this, &MainWindow::do_newValue);
    connect(threadPic, &TPictureThread::newPicture, this, &MainWindow::do_newPicture);

    ui->actDice_Run->setEnabled(false);
    ui->actDice_Pause->setEnabled(false);
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
}

void MainWindow::do_threadA_finished()
{// 与线程的 finished() 信号关联
    ui->statusBar->showMessage("Thread状态：thread finished");
    ui->actThread_Run->setEnabled(true);
    ui->actThread_Quit->setEnabled(false);
}

void MainWindow::do_newValue(int seq, int diceValue)
{// 与线程的 newValue() 信号关联
    QString str = QString::asprintf("第 %d 次掷骰子，点数为：%d", seq, diceValue);
    ui->plainTextEdit->appendPlainText(str);
}

void MainWindow::do_newPicture(QString picName)
{// 与线程的 newPicture() 信号关联
    QPixmap pic(picName); // 加载图片
    ui->labPic->setPixmap(pic); // 显示骰子图片
}

void MainWindow::on_actThread_Run_triggered()
{// “启动线程”按钮
    threadValue->start();
    if(!threadPic->isRunning())
        threadPic->start();
    if(!threadA->isRunning())
        threadA->start();
}


void MainWindow::on_actThread_Quit_triggered()
{// “结束线程”按钮
    threadA->terminate();
    threadA->wait();
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

