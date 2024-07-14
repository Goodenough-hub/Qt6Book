#include "widget.h"
#include "./ui_widget.h"

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/pics/images/background.jpg"));
    QWidget::paintEvent(event);
}

void Widget::closeEvent(QCloseEvent *event)
{
    QString dlgTitle = "消息框";
    QString strInfo = "确定要退出吗";
    QMessageBox::StandardButton result = QMessageBox::question(this, dlgTitle, strInfo, QMessageBox::Yes | QMessageBox::Cancel);
    if(result == QMessageBox::Yes)
        event->accept(); // 接受事件，窗口可以被关闭
    else
        event->ignore(); // 忽略事件，窗口不能被关闭
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QPoint pt = ui->btnMove->pos();
    if((event->key() == Qt::Key_A) || (event->key() == Qt::Key_Left))
        ui->btnMove->move(pt.x()- 20, pt.y());
    else if((event->key() == Qt::Key_D) || (event->key() == Qt::Key_Right))
        ui->btnMove->move(pt.x() + 20, pt.y());
    else if((event->key() == Qt::Key_W) || (event->key() == Qt::Key_Up))
        ui->btnMove->move(pt.x(), pt.y() - 20);
    else if((event->key() == Qt::Key_S) || (event->key() == Qt::Key_Down))
        ui->btnMove->move(pt.x(), pt.y() + 20);

    event->accept(); // 接受事件，不会再传播到父容器组件
}

void Widget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    qDebug("showEvent()函数被触发");
}

void Widget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    qDebug("hideEvent()函数被触发");

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 鼠标左键
    {
        QPoint pt = event->pos(); // 点击点在窗口上的相对坐标
        QPointF relaPt = event->position(); //相对坐标
        QPointF winPt = event->scenePosition(); // 相对坐标
        QPointF globPt = event->globalPosition(); // 屏幕或虚拟桌面上的绝对坐标

        QString str = QString::asprintf("pos()=(%d, %d)", pt.x(), pt.y());
        str = str + QString::asprintf("\nposition()=(%.0f,%.0f", relaPt.x(), relaPt.y());
        str = str + QString::asprintf("\nscenePosition()=(%.0f,%.0f)", winPt.x(), winPt.y());
        str = str + QString::asprintf("\nglobPosition()=(%.0f,%.0f)", globPt.x(), globPt.y());
        ui->labMove->setText(str);
        ui->labMove->adjustSize(); // 自动调整组件大小
        ui->labMove->move(event->pos()); // 标签移动到鼠标光标处
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
