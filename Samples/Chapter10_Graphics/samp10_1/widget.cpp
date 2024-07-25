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

    painter.setPen(QPen(Qt::NoPen)); // 设置画笔，不显示线条
    // 辐射渐变
    QRadialGradient radialGrad(W/2, H/2, qMax(W/8, H/8), W/2, H/2);
    radialGrad.setColorAt(0, Qt::yellow); // 起点颜色
    radialGrad.setColorAt(0.1, Qt::white); // 终点颜色
    radialGrad.setSpread(QGradient::PadSpread); // 延展方式还有RepeatSpread、ReflectSpread
    painter.setBrush(radialGrad);
    painter.drawRect(this->rect()); // 填充更大区域，会有延展效果
    event->accept();
}
