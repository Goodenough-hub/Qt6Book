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
    painter.setRenderHint(QPainter::Antialiasing);
    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度
    QRect rect(W/4, H/4, W/2, H/2); // 中间区域矩形
    // 设置画笔
    QPen pen;
    pen.setWidth(3); // 线宽
    pen.setColor(Qt::red); // 线条颜色
    pen.setStyle(Qt::SolidLine); // 线条样式
    pen.setCapStyle(Qt::FlatCap); // 线条端点样式
    pen.setJoinStyle(Qt::BevelJoin); // 线条的连接样式
    painter.setPen(pen);
    // 设置画刷
    QPixmap texturePixmap(":/Pics/images/texture.jpg");
    QBrush brush;
    brush.setStyle(Qt::TexturePattern); // 画刷填充样式
    brush.setTexture(texturePixmap); // 设置材质图片
    painter.setBrush(brush);
    // 绘图
    painter.drawRect(rect); // 绘制矩形
    event->accept();
}
