#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actListInit_triggered();

    void on_actListClear_triggered();

    void on_actListInsert_triggered();

    void on_actListAppend_triggered();

    void on_actListDelete_triggered();

    void on_actSelAll_triggered();

    void on_tBtnSelNone_triggered();

    void on_tBtnSelInvs_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_chkBoxSorting_clicked(bool checked);

    void on_tBtnSortAsc_clicked();

    void on_tBtnSortDec_clicked();

    void on_tBtnClearText_clicked();

    void on_tBtnAddLine_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
