#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase DB; // 数据库连接
    QSqlRelationalTableModel *tabModel; // 数据库模型
    QItemSelectionModel *selModel; // 选择模型
    void openTable(); // 打开数据表
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpenDB_triggered();

    void on_actFields_triggered();

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actRecDelete_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
