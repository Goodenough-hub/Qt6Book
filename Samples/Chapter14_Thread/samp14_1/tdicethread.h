#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QThread>

class TDiceThread : public QThread
{
    Q_OBJECT
private:
    int m_seq = 0; // 掷骰子次数的序号
    int m_diceValue; // 骰子点数
    bool m_paused = true; // 暂停掷骰子
    bool m_stop = false; // 停止线程，也就是退出 run() 函数的运行
protected:
    void run(); // 线程任务
public:
    explicit TDiceThread(QObject *parent = nullptr);
    void diceBegin(); // 开始掷骰子
    void dicePause(); // 暂停
    void stopThread(); // 结束线程
signals:
    void newValue(int seq, int diceValue); // 产生新点数的信号
};

#endif // TDICETHREAD_H
