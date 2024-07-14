#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->label, &TMyLabel::doubleClicked, this, &Widget::do_doubleClicked);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 双击窗口
    Q_UNUSED(event);
    ui->label->setText("窗口被双击了");
    ui->label->adjustSize();
}

void Widget::do_doubleClicked()
{
    // 双击Label
    ui->label->setText("标签被双击了，信号的槽函数响应");
    ui->label->adjustSize();
}

Widget::~Widget()
{
    delete ui;
}
