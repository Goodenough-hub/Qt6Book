#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    threadDAQ = new TDaqThread(this); // 数据采集线程
    threadShow = new TProcessThread(this); // 数据处理线程
    connect(threadDAQ, &TDaqThread::started, this, &MainWindow::do_threadA_started);
    connect(threadDAQ, &TDaqThread::finished, this, &MainWindow::do_threadA_finished);
    connect(threadShow, &TProcessThread::dataAvailable, this, &MainWindow::do_readBuffer);

    ui->actDice_Run->setEnabled(false);
    ui->actDice_Pause->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_readBuffer(int bufferSeq, int *bufferData, int pointCount)
{
    QString str = QString::asprintf("第 %d 个缓冲区：", bufferSeq);
    for(int i = 0; i < pointCount; i ++)
    {
        str = str + QString::asprintf("%d, ", *bufferData);
        bufferData++;
    }
    str = str + '\n';
    ui->plainTextEdit->appendPlainText(str);
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


void MainWindow::on_actThread_Run_triggered()
{// “启动线程”按钮
    threadShow->start();
    threadDAQ->start();
}


void MainWindow::on_actThread_Quit_triggered()
{// “结束线程”按钮
    threadShow->stopThread();
    threadDAQ->stopThread();
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

