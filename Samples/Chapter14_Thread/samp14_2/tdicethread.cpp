#include "tdicethread.h"
#include <QRandomGenerator>

TDiceThread::TDiceThread(QObject *parent) : QThread{ parent }
{

}

void TDiceThread::diceBegin()
{// 开始掷骰子
    m_paused = false;
}

void TDiceThread::dicePause()
{// 暂停掷骰子
    m_paused = true;
}

void TDiceThread::stopThread()
{// 停止线程
    m_stop = true;
}

bool TDiceThread::readValue(int *seq, int *diceValue)
{
    if(mutex.tryLock(100)) // 尝试锁定互斥量，等待100ms
    { // 如果成功锁定互斥量
        *seq = m_seq;
        *diceValue = m_diceValue;
        mutex.unlock(); // 解锁信号量
        return true;
    }
    else
        return false;
}

void TDiceThread::run()
{// 线程的事件循环
    m_stop = false;
    m_paused = true; // 启动线程后暂时不掷骰子
    m_seq = 0;
    while(!m_stop)
    {
        if(!m_paused)
        {
            mutex.lock(); // 锁定互斥量
            m_diceValue = 0;
            for(int i = 0; i < 5; i ++)
                m_diceValue += QRandomGenerator::global()->bounded(1, 7); // 生成随机数，范围为[1,7)
            m_diceValue = m_diceValue / 5;
            m_seq++;
            mutex.unlock(); // 解锁信号量
        }
        msleep(500); // 线程休眠500ms
    }
    // 在m_stop==true时结束线程任务
    quit(); // 相当于exit(0)，退出线程的事件循环
}
