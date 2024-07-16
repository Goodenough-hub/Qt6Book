#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QCloseEvent>
#include "tdialogsize.h"
#include "tdialogheaders.h"
#include "tdialoglocate.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labCellPos; // 当前单元格行列号，在状态栏上显示
    QLabel *labCellText; // 当前单元格内容，在状态栏上显示
    QStandardItemModel *m_model; // 数据模型
    QItemSelectionModel *m_selection; // 选择模型
    TDialogHeaders *dlgSetHeaders = nullptr; // 设置表头标题对话框，创建一次，重复调用
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_actSetRowColumn_triggered();

    void on_actSetTableHeader_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_actPosCell_triggered();

public slots:
    void do_setCellText(int row, int column, QString &text); // 设置一个单元格的内容
signals:
    void cellIndexChanged(int rowNo, int colNo); // 当前单元格发生变化
private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override; // 事件处理函数，关闭窗口时，询问是否退出
};
#endif // MAINWINDOW_H
