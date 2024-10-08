#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    // ui->battery->setPowerLevel(value); // 设置电池电量
}


void Widget::on_battery_powerLevelChanged(int arg1)
{
    QString str = QString::asprintf("当前电量：%d %%", arg1);
    ui->labInfo->setText(str);
}

