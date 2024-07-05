#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 将表盘、滑动条、卷滚条的valueChanged()信号与自定义槽函数关联
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(do_valueChanged(int)));
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(do_valueChanged(int)));
    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(do_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_valueChanged(int value)
{
    // 自定义槽函数
    ui->progressBar->setValue(value);
}

void Widget::on_checkBox_Visible_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void Widget::on_checkBox_Inverted_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void Widget::on_radioButton_Percent_clicked()
{
    ui->progressBar->setFormat("%p%");
}


void Widget::on_radioButton_Value_clicked()
{
    ui->progressBar->setFormat("%v");
}

