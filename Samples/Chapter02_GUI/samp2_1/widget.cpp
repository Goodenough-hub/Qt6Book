#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setText("欢迎使用QT6");
    ui->btnClose->setText("关闭");
}

Widget::~Widget()
{
    delete ui;
}
