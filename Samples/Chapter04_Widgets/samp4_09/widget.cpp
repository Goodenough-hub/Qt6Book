#include "widget.h"
#include "./ui_widget.h"

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

void Widget::on_btnIniItems_clicked()
{
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");
    ui->comboBox_simple->clear();
    for(int i = 0; i < 20; i ++)
        ui->comboBox_simple->addItem(icon, QString("Item %1").arg(i));
        // ui->comboBox_simple->addItem(QString("Item %1").arg(i));
}


void Widget::on_btnCLearList_clicked()
{
    ui->comboBox_simple->clear();
}


void Widget::on_btnIni2_clicked()
{
    // QMap自动按照key排序
    QMap<QString, int> City_Zone;
    City_Zone.insert("北京", 10);
    City_Zone.insert("上海", 21);
    City_Zone.insert("天津", 22);
    City_Zone.insert("大连", 411);
    City_Zone.insert("锦州", 416);
    City_Zone.insert("徐州", 516);
    City_Zone.insert("福州", 591);
    City_Zone.insert("青岛", 532);
    ui->comboBox_city->clear();
    foreach(const QString &str, City_Zone.keys())
        ui->comboBox_city->addItem(str, City_Zone.value(str));
}


void Widget::on_comboBox_simple_currentTextChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}


void Widget::on_comboBox_city_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString city = ui->comboBox_city->currentText();
    QString zone = ui->comboBox_city->currentData().toString();
    ui->plainTextEdit->appendPlainText(city + ": 区号 = " + zone);
}


void Widget::on_btnClearEdit_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_chkboxEdit_clicked(bool checked)
{
    if(checked)
    {
        ui->comboBox_simple->setEditable(true);
    }
}

