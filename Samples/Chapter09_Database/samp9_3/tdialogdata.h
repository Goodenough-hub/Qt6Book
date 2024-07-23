#ifndef TDIALOGDATA_H
#define TDIALOGDATA_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>

namespace Ui {
class TDialogData;
}

class TDialogData : public QDialog
{
    Q_OBJECT
private:
    QSqlRecord m_record; // 保存一条记录的数据
public:
    explicit TDialogData(QWidget *parent = nullptr);
    ~TDialogData();

    void setUpdateRecord(QSqlRecord &recData); // 更新数据
    void setInsertRecord(QSqlRecord &recData); // 插入记录
    QSqlRecord getRecordData(); // 获取界面中输入的数据

private slots:
    void on_btnClearPhoto_clicked();

    void on_btnSetPhoto_clicked();

private:
    Ui::TDialogData *ui;
};

#endif // TDIALOGDATA_H
