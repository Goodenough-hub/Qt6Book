#ifndef TGRAPHICSVIEW_H
#define TGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TGraphicsView(QWidget *parent=nullptr);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

signals:
    void mouseMovePoint(QPoint point); // 鼠标移动
    void mouseClicked(QPoint point); // 鼠标单击
    void mouseDoubleClick(QPoint point); // 双击事件
    void keyPress(QKeyEvent *event); // 按键事件
};

#endif // TGRAPHICSVIEW_H
