#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    this->resize(300, 300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int W = width();
    int H = height();
    int side = qMin(W, H);
    QRect rect((W-side)/2, (H-side)/2, side, side); // 视口矩形区
    painter.drawRect(rect); // 绘制视口边界
    painter.setViewport(rect); // 设置视口
    painter.setWindow(-100, -100, 200, 200); // 设置窗口坐标系
    // 设置画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);

    // 线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0); // 从左到右
    linearGrad.setColorAt(0, Qt::yellow); // 起点颜色
    linearGrad.setColorAt(1, Qt::green); // 终点颜色
    linearGrad.setSpread(QGradient::PadSpread); // 展布模式
    painter.setBrush(linearGrad);

    // 设置组合模式
    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    // painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
    // painter.setCompositionMode(QPainter::CompositionMode_Exclusion);


    for(int i = 0; i < 36; i ++)
    {
        painter.drawEllipse(QPoint(50, 0), 50, 50);
        painter.rotate(10);
    }
    event->accept();
}
