#include "tdicethread.h"
#include <QRandomGenerator>
#include <QReadWriteLock>
#include <QWaitCondition>

QReadWriteLock rwLocker; // 读写锁
QWaitCondition waiter; // 等待条件
int seq = 0, diceValue = 0;

TDiceThread::TDiceThread(QObject *parent) : QThread{ parent }
{

}

TValueThread::TValueThread(QObject *parent) : QThread{ parent }
{

}

TPictureThread::TPictureThread(QObject *parent) : QThread{ parent }
{

}


void TDiceThread::run()
{// 线程的任务
    seq = 0;
    while(1)
    {
        rwLocker.lockForWrite(); // 以写入的方式锁定
        diceValue = QRandomGenerator::global()->bounded(1, 7);
        seq ++;
        rwLocker.unlock(); // 解锁
        waiter.wakeAll(); // 唤醒其他等待的线程
        msleep(500);
    }
}

void TValueThread::run()
{
    while(1)
    {
        rwLocker.lockForRead(); // 以只读方式锁定
        waiter.wait(&rwLocker); // 等待被唤醒
        emit newValue(seq, diceValue);
        rwLocker.unlock(); // 解锁
    }
}

void TPictureThread::run()
{
    while(1)
    {
        rwLocker.lockForRead(); // 以只读方式锁定
        waiter.wait(&rwLocker); // 等待被唤醒
        QString filename = QString::asprintf(":/icons/images/d%d.jpg", diceValue);
        emit newPicture(filename);
        rwLocker.unlock(); // 解锁
    }
}
