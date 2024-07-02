#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->comboBox->addItem("D:\\Project\\QT\\Qt6Book\\Samples\\Chapter04_Widgets\\samp4_02\\widget.ui");
    ui->comboBox_2->addItem("\\");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showBoolInfo(QString str, bool CheckValue)
{
    if(CheckValue)
        ui->plainTextEdit->appendPlainText(str + "= true");
    else
        ui->plainTextEdit->appendPlainText(str + "= false");
}

void Widget::on_pushButton_25_clicked()
{
    // 测试isNull()和isEmpty()函数
    ui->plainTextEdit->appendPlainText("\n===isNull()函数测试");
    QString str1, str2="";
    ui->plainTextEdit->appendPlainText("QString str1, str2=""");
    showBoolInfo("str1.isNull()", str1.isNull());
    showBoolInfo("str1.isEmpty()", str1.isEmpty());
    showBoolInfo("\nstr2.isNull()",str2.isNull());
    showBoolInfo("str2.isEmpty()", str2.isEmpty());
    str2.clear();
    ui->plainTextEdit->appendPlainText("\nstr2.clear()后");
    showBoolInfo("\nstr2.isNull()", str2.isNull());
    showBoolInfo("str2.isEmpty()", str2.isEmpty());
}


void Widget::on_pushButton_2_clicked()
{
    // 测试first()和last函数()
    ui->plainTextEdit->appendPlainText("\n===first(), last()函数测试");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1);
    ui->plainTextEdit->appendPlainText("str2= " + str2);

    int N = str1.lastIndexOf(str2);
    QString str3 = str1.first(N + 1);
    ui->plainTextEdit->appendPlainText(str3);
    str3 = str1.last(str1.size() - N - 1);
    ui->plainTextEdit->appendPlainText(str3);
}


void Widget::on_pushButton_3_clicked()
{
    // 测试left()和right()函数
    ui->plainTextEdit->appendPlainText("\n===left(), right()函数测试\n提取左边5个字符\n提取右边5个字符");
    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1 + '\n');
    ui->plainTextEdit->appendPlainText("\nstr1.left(5)=" + str1.left(5));
    ui->plainTextEdit->appendPlainText("\nstr1.right(5)=" + str1.right(5));
}


void Widget::on_pushButton_clicked()
{
    // 测试front()和back()函数
    ui->plainTextEdit->appendPlainText("\n===front(), back()函数测试");
    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1 + '\n');
    ui->plainTextEdit->appendPlainText("\nstr1.front()=" + QString(str1.front()));
    ui->plainTextEdit->appendPlainText("\nstr1.back()=" + QString(str1.back()));
}


void Widget::on_pushButton_4_clicked()
{
    // 测试section()函数
    ui->plainTextEdit->appendPlainText("\n===section()函数测试\n以str2作为分隔符[0, 1]");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1);
    ui->plainTextEdit->appendPlainText("str2= " + str2);
    QString str3 = str1.section(str2, 0, 1);
    ui->plainTextEdit->appendPlainText("\n" + str3);
}


void Widget::on_pushButton_26_clicked()
{
    // 测试resize()函数
    ui->plainTextEdit->appendPlainText("\n===resize()函数测试\n长度为5,用0填充");
    QString str2 = ui->comboBox_2->currentText();
    ui->plainTextEdit->appendPlainText("str2= " + str2);
    str2.resize(5, '0');
    ui->plainTextEdit->appendPlainText("\nstr2.resize = "+ str2);
}


void Widget::on_pushButton_27_clicked()
{
    // 测试size()和length()函数
    ui->plainTextEdit->appendPlainText("\n===size()函数，length()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    ui->plainTextEdit->appendPlainText("str1= " + str1);
    QString str_size = QString::number(str1.size());
    ui->plainTextEdit->appendPlainText("\nstr1.size() = "+ str_size);

    QString str_len = QString::number(str1.length());
    ui->plainTextEdit->appendPlainText("\nstr1.length() = "+ str_len);
}


void Widget::on_pushButton_5_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_pushButton_28_clicked()
{
    // 测试fill()函数
    ui->plainTextEdit->appendPlainText("\n===fill()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    int num = ui->spinBox->value();
    str1.fill(str2[0], num);
    ui->plainTextEdit->appendPlainText("str1.fill() =  " + str1);
}


void Widget::on_pushButton_29_clicked()
{
    // 测试indexOf()函数、lastIndexOf()函数
    ui->plainTextEdit->appendPlainText("\n===indexOf()函数，lastIndexOf()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();

    int N = str1.indexOf(str2);
    int num = str1.lastIndexOf(str2);
    ui->plainTextEdit->appendPlainText("str1.indexOf(str2) = " + QString::number(N) + "\nstr1.lastIndexOf(str2) = " + QString::number(num));
}


void Widget::on_pushButton_30_clicked()
{
    // 测试contains()函数
    ui->plainTextEdit->appendPlainText("\n===contains()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    bool isContains = str1.contains(str2);
    showBoolInfo("str1.contains(str2) = ", isContains);
}


void Widget::on_pushButton_31_clicked()
{
    // 测试endsWith()函数，startsWith()函数
    ui->plainTextEdit->appendPlainText("\n===contains()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    showBoolInfo("str1.endsWith(\".ui\")", str1.endsWith(".ui"));
    showBoolInfo("str1.startsWith(\"d:\")", str1.startsWith("d:"));
}


void Widget::on_pushButton_32_clicked()
{
    // 测试count()函数
    ui->plainTextEdit->appendPlainText("\n===count()函数测试\n");
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    int count = str1.count(str2);
    ui->plainTextEdit->appendPlainText("str1.count(str2) = " + QString::number(count));
}


void Widget::on_pushButton_45_clicked()
{
    // 测试trimmed()函数，simplified()函数
    ui->plainTextEdit->appendPlainText("\n===trimmed()函数测试，simplified()函数测试\n");
    QString str = "   Are you    ok?";
    QString str1 = str.trimmed();
    QString str2 = str.simplified();
    ui->plainTextEdit->appendPlainText("str = " + str + "\nstr.trimmed() = " + str1 + "\nstr.simplified = " + str2);
}


void Widget::on_pushButton_46_clicked()
{
    // 测试insert()函数
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    int num = ui->spinBox->value();
    str1.insert(num, str2);
    ui->plainTextEdit->appendPlainText("str1.insert(" + QString::number(num) + ", str2) = "+ str1);
}


void Widget::on_pushButton_47_clicked()
{
    // 测试remove()函数
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    int num = ui->spinBox->value();
    int lastIndex = str1.lastIndexOf(str2);
    str1.remove(lastIndex + 1, num);
    ui->plainTextEdit->appendPlainText("str1.remove(" + QString::number(lastIndex) + ", " + QString::number(num) + ") = " + str1);
}


void Widget::on_pushButton_48_clicked()
{
    // 测试replace()函数
    QString str1 = ui->comboBox->currentText();
    QString str2 = ui->comboBox_2->currentText();
    int num = ui->spinBox->value();
    int lastIndex = str1.lastIndexOf(str2);
    str1.replace(lastIndex + 1, num, "OK !");
    ui->plainTextEdit->appendPlainText("str1.replace(" + QString::number(lastIndex) + ", " + QString::number(num) + ", \"OK !\") = " + str1);
}

