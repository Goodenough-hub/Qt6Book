#ifndef TDIALOGSIZE_H
#define TDIALOGSIZE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TDialogSize;
}

class TDialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit TDialogSize(QWidget *parent = nullptr);
    ~TDialogSize();
    int rowCount(); // 获取对话框输入的行数
    int columnCount(); // 获取对话框输入的列数
    void setRowColumn(int row, int column); // 设置对话框上两个SpinBox的值

private:
    Ui::TDialogSize *ui;
};

#endif // TDIALOGSIZE_H
