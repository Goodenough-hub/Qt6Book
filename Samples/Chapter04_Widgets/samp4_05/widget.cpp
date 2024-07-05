#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->chkBox_Enable->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_Align_Center_clicked()
{
    ui->editInput->setAlignment(Qt::AlignLeft);
}


void Widget::on_btnAlign_left_clicked()
{
    ui->editInput->setAlignment(Qt::AlignCenter);
}


void Widget::on_btn_Align_Right_clicked()
{
    ui->editInput->setAlignment(Qt::AlignRight);
}


void Widget::on_btnFont_Bold_clicked(bool checked)
{
    QFont font = ui->editInput->font();
    font.setBold(checked);
    ui->editInput->setFont(font);
}


void Widget::on_btn_Font_Italic_clicked(bool checked)
{
    QFont font = ui->editInput->font();
    font.setItalic(checked);
    ui->editInput->setFont(font);
}


void Widget::on_btnFont_UnderLine_clicked(bool checked)
{
    QFont font = ui->editInput->font();
    font.setUnderline(checked);
    ui->editInput->setFont(font);
}


void Widget::on_checkBox_ClearButton_clicked(bool checked)
{
    ui->editInput->setClearButtonEnabled(checked);
}


void Widget::on_chkBox_Readonly_clicked(bool checked)
{
    ui->editInput->setReadOnly(checked);
}


void Widget::on_chkBox_Enable_clicked(bool checked)
{
    ui->editInput->setEnabled(checked);
}


void Widget::on_radioBlack_clicked()
{
    QPalette plet = ui->editInput->palette();
    plet.setColor(QPalette::Text, Qt::black);
    ui->editInput->setPalette(plet);
}


void Widget::on_radioRed_clicked()
{
    QPalette plet = ui->editInput->palette();
    plet.setColor(QPalette::Text, Qt::red);
    ui->editInput->setPalette(plet);
}


void Widget::on_radioBlue_clicked()
{
    QPalette plet = ui->editInput->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    ui->editInput->setPalette(plet);
}

