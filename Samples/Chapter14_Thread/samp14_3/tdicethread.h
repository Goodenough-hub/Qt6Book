#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QThread>

// TDiceThread 是生成骰子点数的线程
class TDiceThread : public QThread
{
    Q_OBJECT
private:
    int m_seq = 0; // 掷骰子次数的序号
    int m_diceValue; // 骰子点数
protected:
    void run(); // 线程的任务函数
public:
    explicit TDiceThread(QObject *parent = nullptr);
    void diceBegin(); // 开始掷骰子
    void dicePause(); // 暂停
    void stopThread(); // 结束线程

};

// TValueThread 获取骰子点数
class TValueThread : public QThread
{
    Q_OBJECT

protected:
    void run(); // 线程的人数函数
public:
    explicit TValueThread(QObject *parent = nullptr);
signals:
    void newValue(int seq, int diceValue);
};

// TPictureThread 获取骰子点数，生成对应的图片文件名
class TPictureThread : public QThread
{
    Q_OBJECT

protected:
    void run(); // 线程的人数函数
public:
    explicit TPictureThread(QObject *parent = nullptr);

signals:
    void newPicture(QString picName);
};

#endif // TDICETHREAD_H
