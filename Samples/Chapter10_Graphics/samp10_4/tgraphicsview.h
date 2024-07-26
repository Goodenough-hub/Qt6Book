#ifndef TGRAPHICSVIEW_H
#define TGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TGraphicsView(QWidget *parent=nullptr);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
};

#endif // TGRAPHICSVIEW_H
