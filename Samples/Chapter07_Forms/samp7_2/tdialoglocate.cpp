#include "tdialoglocate.h"
#include "ui_tdialoglocate.h"

TDialogLocate::TDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogLocate)
{
    ui->setupUi(this);
}

TDialogLocate::~TDialogLocate()
{
    QMessageBox::information(this, "提示", "TDialogLocate对话框被删除");
    delete ui;
}

void TDialogLocate::setSpinRange(int rowCount, int colCount)
{
    // 设置spinBox的最大值
    ui->spinBox_Col->setMaximum(colCount - 1);
    ui->spinBox_Row->setMaximum(rowCount - 1);
}

void TDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinBox_Col->setValue(colNo);
    ui->spinBox_Row->setValue(rowNo);
}

void TDialogLocate::closeEvent(QCloseEvent *event)
{
    // 对话框关闭时
    event->accept();
    emit changedActionEnabled(true); // 发射信号
}

void TDialogLocate::showEvent(QShowEvent *event)
{
    // 对话框显示时
    event->accept();
    emit changedActionEnabled(true);
}

void TDialogLocate::on_btnSetFont_clicked()
{
    // 定位到单元格并设置文字
    int row = ui->spinBox_Row->value(); // 行号
    int col = ui->spinBox_Col->value(); // 列号
    QString text = ui->lineEdit->text(); // 文字
    emit changeCellText(row, col, text); // 发射信号
    if(ui->chkRowInc->isChecked()) // 行增
        ui->spinBox_Row->setValue(1 + ui->spinBox_Row->value());
    if(ui->chkColumnInc->isChecked()) // 列增
        ui->spinBox_Col->setValue(1 + ui->spinBox_Col->value());
}

