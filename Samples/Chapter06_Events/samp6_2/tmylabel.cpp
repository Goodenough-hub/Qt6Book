#include "tmylabel.h"

TMyLabel::TMyLabel(QWidget *parent):QLabel(parent)
{
    this->setAttribute(Qt::WA_Hover, true); // 必须设置这个属性，否则不能产生hover事件
}

void TMyLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}

bool TMyLabel::event(QEvent *event)
{
    if(event->type() == QEvent::HoverEnter) // 光标移入
    {
        QPalette plet = this->palette();
        plet.setColor(QPalette::WindowText, Qt::red);
        this->setPalette(plet);
    }
    else if(event->type() == QEvent::HoverLeave)
    {
        QPalette plet = this->palette();
        plet.setColor(QPalette::WindowText, Qt::black);
        this->setPalette(plet);
    }
    return QLabel::event(event); // 运行父类的event()，处理其它类型事件
}
