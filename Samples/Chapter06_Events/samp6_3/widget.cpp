#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->labHover->installEventFilter(this); // 安装事件过滤器
    ui->labDBClick->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    // 上面的QLabel组件的事件处理
    if(watched == ui->labHover)
    {
        if(event->type() == QEvent::Enter) // 鼠标光标移入
            ui->labHover->setStyleSheet("background-color:rgb(170, 255, 255);");
        else if(event->type() == QEvent::Leave) // 鼠标光标离开
        {
            ui->labHover->setStyleSheet("");
            ui->labHover->setText("靠近我，点击我");
        }
        else if(event->type() == QEvent::MouseButtonPress) // 鼠标键按下
            ui->labHover->setText("button pressed");
        else if(event->type() == QEvent::MouseButtonRelease) // 鼠标键释放
            ui->labHover->setText("button released");
    }

    // 下面的QLabel组件的事件处理
    if(watched == ui->labDBClick)
    {
        if(event->type() == QEvent::Enter) // 鼠标光标移入
            ui->labDBClick->setStyleSheet("background-color:rgb(85, 255, 127);");
        else if(event->type() == QEvent::Leave) // 鼠标光标离开
        {
            ui->labDBClick->setStyleSheet("");
            ui->labDBClick->setText("可双击的标签");
        }
        else if(event->type() == QEvent::MouseButtonDblClick) // 鼠标双击
            ui->labDBClick->setText("double clicked");
    }
    return QWidget::eventFilter(watched, event); // 运行父类的eventFilter()函数
    // return true; // 有问题，不能直接返回true
}
