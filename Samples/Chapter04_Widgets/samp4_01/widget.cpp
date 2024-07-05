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

void Widget::on_btnGetChars_clicked()
{
    QString str = ui->editStr->toPlainText();

    // 读取输入的字符串
    if(str.isEmpty())
        return;
    ui->plainTextEdit->clear();
    for(qint16 i = 0; i < str.size(); i ++)
    {
        QChar ch = str.at(i); // 获取单个字符
        char16_t uniCode = ch.unicode(); // 获取QChar字符的UTF-16编码：char16_t 和 char32_t 是用于表示 Unicode 字符集中字符的数据类型，分别用于表示 16 位和 32 位的 Unicode 字符。
        QString chStr(ch); // 将QChar字符串转换为QString字符串
        QString info = chStr + QString::asprintf("\t, Unicode编码=%x%X",uniCode);
        ui->plainTextEdit->appendPlainText(info);
    }
}


void Widget::on_btnCharJude_clicked()
{
    QString str = ui->editChar->toPlainText();
    if(str.isEmpty())
        return ;
    QChar ch = str[0];
    char16_t uniCode = ch.unicode();
    QString chStr(ch);
    QString info = chStr + QString::asprintf("\t,Unicode 编码= %x%X\n", uniCode);
    ui->plainTextEdit->appendPlainText(info);

    // 使用QChar的接口函数判断字符的特性
    ui->chkDigit->setChecked(ch.isDigit());
    ui->chkLetter->setChecked(ch.isLetter());
    ui->chkLetterOrNumber->setChecked(ch.isLetterOrNumber());
    ui->chkUpper->setChecked(ch.isUpper());
    ui->chkLower->setChecked(ch.isLower());
    ui->chkMark->setChecked(ch.isMark()); // 是否是记号
    ui->chkSpace->setChecked(ch.isSpace()); // 是否分隔符号
    ui->chkSymbol->setChecked(ch.isSymbol()); // 是否是符号
    ui->chkPunct->setChecked(ch.isPunct()); // 是否是标点符号
}


void Widget::on_btnConvLatin1_clicked()
{
    QString str = "Dimple";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);
    QChar chP = QChar::fromLatin1('P');
    // QChar chP = QChar('P');
    str[0] = chP;
    ui->plainTextEdit->appendPlainText("\n" + str);
}


void Widget::on_btnConvUTF16_clicked()
{
    QString str = "Hello,北京";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);
    str[6] = QChar(0x9752); // '青'
    str[7] = QChar::fromUcs2(0x5C9B); // '岛'
    ui->plainTextEdit->appendPlainText("\n" + str);
}


void Widget::on_btnCompare_clicked()
{
    QString str = "他们来自于河南或河北";
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str);
    QString HuStr = "河to湖";
    QChar He = QChar::fromUcs2(HuStr[0].unicode());
    QChar Hu = QChar(HuStr[3].unicode());
    for(qint16 i = 0; i < str.size(); i ++)
    {
        if(str.at(i) == He)
            str[i] = Hu;
    }
    ui->plainTextEdit->appendPlainText("\n" + str);
}


void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

