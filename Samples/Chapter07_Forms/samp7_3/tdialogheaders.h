#ifndef TDIALOGHEADERS_H
#define TDIALOGHEADERS_H

#include <QDialog>
#include <QStringListModel>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class TDialogHeaders;
}

class TDialogHeaders : public QDialog
{
    Q_OBJECT
private:
    QStringListModel *m_model; // 数据模型，存储字符串列表数据
public:
    explicit TDialogHeaders(QWidget *parent = nullptr);
    ~TDialogHeaders();
    void setHeaderList(QStringList& headers); // 设置字符串列表
    QStringList headerList(); // 返回字符串列表

private:
    Ui::TDialogHeaders *ui;
};

#endif // TDIALOGHEADERS_H
