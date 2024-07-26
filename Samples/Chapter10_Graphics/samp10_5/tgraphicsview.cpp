#include "tgraphicsview.h"

TGraphicsView::TGraphicsView(QWidget *parent) {}

void TGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos(); // 视图中的坐标
        emit mouseClicked(point); // 发射信号
    }
    QGraphicsView::mousePressEvent(event);
}

void TGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动事件
    QPoint point = event->pos(); // 视图中的坐标
    emit mouseMovePoint(point); // 发射信号
    QGraphicsView::mouseMoveEvent(event);
}

void TGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 鼠标双击事件
    if(event->button()==Qt::LeftButton)
    {
        QPoint point = event->pos();
        emit mouseDoubleClick(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void TGraphicsView::keyPressEvent(QKeyEvent *event)
{
    // 按键事件
    emit keyPress(event); // 发射信号
    QGraphicsView::keyPressEvent(event);
}
