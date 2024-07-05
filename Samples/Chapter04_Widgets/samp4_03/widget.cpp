#include "widget.h"
#include "./ui_widget.h"
#include <QRegularExpressionValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 第一个数字是1-9，第二个数字和之后的数字是0-9
    QRegularExpression regx ( "[1-9][0-9]+$" );
    QValidator *validator = new QRegularExpressionValidator(regx, this);
    ui->editNum->setValidator(validator);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCal_clicked()
{
    // “计算总价”按钮
    int num = ui->editNum->text().toInt();
    float price = ui->editPrice->text().toFloat();
    float total = num * price;
    QString str;
    str = str.setNum(total, 'f', 2); // 保留两位小数
    ui->editTotal->setText(str);
}


void Widget::on_btnDec_clicked()
{
    // 读取十进制字符串，将其转换为其他进制显示
    int val = ui->editDec->text().toInt();
    QString str = QString::number(val, 16); // 转为十六进制
    str = str.toUpper();
    ui->editHex->setText(str);
    str = QString::number(val, 2); // 转为二进制
    ui->editBin->setText(str);
}


void Widget::on_btnBin_clicked()
{
    // 读取二进制字符串，将其转换为其他进制显示
    bool ok;
    int val = ui->editBin->text().toInt(&ok, 2);
    QString str = QString::number(val, 10); // 转为十进制
    ui->editDec->setText(str);
    str = QString::number(val, 16); // 转为十六进制
    str = str.toUpper();
    ui->editHex->setText(str);
}


void Widget::on_btnHex_clicked()
{
    // 读取十六进制字符串，将其转换为其他进制显示
    bool ok;
    int val = ui->editHex->text().toInt(&ok, 16);
    if(ok != NULL)
    {
        QString str = QString::number(val, 10); // 转为十进制
        ui->editDec->setText(str);
        str = QString::number(val, 2); // 转为十六进制
        ui->editBin->setText(str);
    }
}


void Widget::on_btnDebug_clicked()
{
    // “qDebug()测试”按钮
    // ====setNum()函数，浮点数
    QString str;
    double num = 1245.2783;
    qDebug("num = %f", num);
    str.setNum(num, 'f', 5);
    qDebug("str = %s", str.toLocal8Bit().data());
    str.setNum(num, 'E', 5);
    qDebug("str = %s", str.toLocal8Bit().data());
    str.setNum(num, 'g', 5);
    qDebug("str = %s", str.toLocal8Bit().data());
    str.setNum(num, 'g', 3);
    qDebug("str = %s", str.toLocal8Bit().data());
}

