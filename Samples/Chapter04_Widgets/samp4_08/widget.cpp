#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // “定时器”和“计时器精度”分组框在垂直方向上设置为固定尺寸
    ui->groupBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ui->groupBox_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_timer = new QTimer(this); // 创建定时器
    m_timer->stop(); // 先停止定时器
    m_timer->setTimerType(Qt::CoarseTimer); // 定时器精度
    ui->radioCoarse->setChecked(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timerTimeout()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnStart_clicked()
{
    m_timer->setInterval(ui->spinBoxIntv->value());
    if(ui->radioContinue->isChecked())
        m_timer->setSingleShot(false);
    else m_timer->setSingleShot(true);

    //设置定时器精度
    if(ui->radioPrecise->isChecked())
        m_timer->setTimerType(Qt::PreciseTimer);
    else if(ui->radioCoarse->isChecked())
        m_timer->setTimerType(Qt::CoarseTimer);
    else m_timer->setTimerType(Qt::VeryCoarseTimer);

    m_timer->start();
    m_counter.start();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}


void Widget::on_btnStop_clicked()
{
    m_timer->stop();
    int tmMsec = m_counter.elapsed();
    int ms = tmMsec = tmMsec % 1000;
    int sec = tmMsec/ 1000;
    QString str = QString("流逝的时间：%1秒，%2毫秒").arg(sec).arg(ms, 3, 10, QChar('0'));
    ui->labelElapsedTime->setText(str);

    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnOneShot->setEnabled(true);
}

void Widget::do_timerTimeout()
{
    // 与定时器的timeout()信号相关联的槽函数
    QApplication::beep(); // 使系统“滴”一声
    QTime curTime = QTime::currentTime();
    ui->LCDHour->display(curTime.hour());
    ui->LCDMin->display(curTime.minute());
    ui->LCDSec->display(curTime.second());
    if(m_timer->isSingleShot())
    {
        int tmMsec = m_counter.elapsed();
        QString str = QString("流逝的时间：%1毫秒").arg(tmMsec);
        ui->labelElapsedTime->setText(str);
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->btnOneShot->setEnabled(true);
    }
}

void Widget::do_timer_shot()
{
    QApplication::beep();
    int tmMsec = m_counter.elapsed();
    QString str = QString("流逝的时间：%1毫秒").arg(tmMsec);
    ui->labelElapsedTime->setText(str);
    ui->btnOneShot->setEnabled(true);
}


void Widget::on_btnOneShot_clicked()
{
    int intv = ui->spinBoxIntv->value();
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &Widget::do_timer_shot);
    m_counter.start();
    ui->btnOneShot->setEnabled(false);
}

