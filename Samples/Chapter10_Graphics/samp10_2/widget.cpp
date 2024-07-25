#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white)); // 设置窗口背景色
    setAutoFillBackground(true);
    resize(600, 300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    // 生成五角星的5个顶点，假设原点在五角星中心
    qreal R=100; // 半径
    const qreal Pi = 3.14159;
    qreal deg = Pi*72/180;
    QPoint points[5] = {QPoint(R, 0),
                            QPoint(R * qCos(deg), -R * qSin(deg)),
                            QPoint(R * qCos(2 * deg), -R * qSin(2 * deg)),
                            QPoint(R * qCos(3 * deg), -R * qSin(3 * deg)),
                            QPoint(R * qCos(4 * deg), -R * qSin(4 * deg)) };

    // 设置字体
    QFont font;
    font.setPointSize(14);
    painter.setFont(font);
    // 设置画笔
    QPen penLine;
    penLine.setWidth(2);
    penLine.setColor(Qt::blue);
    penLine.setStyle(Qt::SolidLine);
    penLine.setCapStyle(Qt::FlatCap);
    penLine.setJoinStyle(Qt::BevelJoin);
    painter.setPen(penLine);
    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern); // 画刷填充样式
    painter.setBrush(brush);

    // 设计绘制五角星的PainterPath，以便重复使用
    QPainterPath startPath;
    startPath.moveTo(points[0]);
    startPath.lineTo(points[2]);
    startPath.lineTo(points[4]);
    startPath.lineTo(points[1]);
    startPath.lineTo(points[3]);
    startPath.closeSubpath(); // 闭合路径，最后一个点与第一个点相连
    startPath.addText(points[0], font, "1"); // 显示顶点编号
    startPath.addText(points[1], font, "2");
    startPath.addText(points[2], font, "3");
    startPath.addText(points[3], font, "4");
    startPath.addText(points[4], font, "5");

    // 绘图，第一个五角星
    painter.save(); // 保存坐标状态
    painter.translate(100, 120);
    painter.drawPath(startPath); // 画五角星
    painter.drawText(0, 0, "S1");
    painter.restore(); // 恢复坐标状态
    // 第二个五角星
    painter.translate(300, 120); // 平移
    painter.scale(0.8, 0.8); // 缩放
    painter.rotate(90); // 顺时针旋转
    painter.drawPath(startPath); // 画五角星
    painter.drawText(0, 0, "S2");
    // 第三个五角星
    painter.resetTransform(); // 复位所有坐标变换
    painter.translate(500, 120); // 平移
    painter.rotate(-145); // 逆时针旋转
    painter.drawPath(startPath); // 画五角星
    painter.drawText(0, 0, "S3");
    event->accept();
}
