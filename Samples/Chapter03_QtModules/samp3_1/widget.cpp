#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    boy = new TPerson("王小明", this);
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy");
    connect(boy, SIGNAL(ageChanged(int)), this, SLOT(do_ageChanged(int)));

    girl = new TPerson("张小丽", this);
    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl");
    connect(girl, SIGNAL(ageChanged(int)), this, SLOT(do_ageChanged(int)));

    ui->spinBox_boy->setProperty("isBoy", true);
    ui->spinBox_girl->setProperty("isBoy", false);
    connect(ui->spinBox_girl, SIGNAL(valueChanged(int)), this, SLOT(do_spinChanged(int)));
    connect(ui->spinBox_boy, &QSpinBox::valueChanged, this, &Widget::do_spinChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_ageChanged(int value)
{
    Q_UNUSED(value);
    TPerson *person = qobject_cast<TPerson *>(sender()); // 获取信号发射者
    QString hisName = person->property("name").toString(); // 姓名
    QString hisSex = person->property("sex").toString();
    int hisAge = person->age(); // 通过接口函数获取年龄
    // int hisAge = person->property("age").toInt(); // 通过属性获取年龄数据
    QString str = QString("%1, %2, 年龄=%3").arg(hisName).arg(hisSex).arg(hisAge);
    ui->plainTextEdit->appendPlainText(str);
}

void Widget::do_spinChanged(int arg1)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(sender());
    if(spinBox->property("isBoy").toBool())
    {
        boy->setAge(arg1);
    }
    else girl->setAge(arg1);
}

void Widget::on_btnMeta_clicked()
{
    // "元对象信息"按钮
    QObject *obj = boy;
    const QMetaObject *meta = obj->metaObject();
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(QString("类名称：%1\n").arg(meta->className()));
    ui->plainTextEdit->appendPlainText("property");
    for(int i = meta->propertyOffset(); i < meta->propertyCount(); i ++)
    {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = obj->property(propName).toString();
        QString str = QString("属性名称=%1，属性值=%2").arg(propName).arg(propValue);
        ui->plainTextEdit->appendPlainText(str);
    }
    //获取类的信息
    ui->plainTextEdit->appendPlainText("");
    ui->plainTextEdit->appendPlainText("classinfo");
    for(int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++ i)
    {
        QMetaClassInfo classinfo = meta->classInfo(i);
        ui->plainTextEdit->appendPlainText(
            QString("Name=%1，Value=%2").arg(classinfo.name()).arg(classinfo.value()));
    }
}

void Widget::on_btnClean_clicked()
{
    ui->plainTextEdit->setPlainText("");
}


void Widget::on_btnBoyInc_clicked()
{
    boy->incAge();
}


void Widget::on_btnGirlInc_clicked()
{
    girl->incAge();
}

