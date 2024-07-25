#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white)); // 设置窗口为白色背景
    setAutoFillBackground(true);
    this->resize(400, 300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // 创建QPainter对象
    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度
    QRect rect(W/4, H/4, W/2, H/2); // 中间区域矩形
    painter.setPen(QPen(Qt::NoPen)); // 设置画笔，不显示线条
    // 线性渐变
    QLinearGradient linearGrad(rect.left(), rect.top(), rect.right(), rect.top()); // 从左到右
    linearGrad.setColorAt(0, Qt::blue); // 起点颜色
    linearGrad.setColorAt(0.5, Qt::white); // 中间点颜色
    linearGrad.setColorAt(1, Qt::blue); // 终点颜色
    painter.setBrush(linearGrad);
    painter.drawRect(rect); // 绘制矩形
    event->accept();
}
