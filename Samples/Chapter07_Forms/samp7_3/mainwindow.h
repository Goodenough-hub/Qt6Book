#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include "tformdoc.h"
#include "tformtable.h"

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
    void do_changeTabTitle(QString title); // 用于设置tabWidget当前页的标题
    void on_actWidgetInsite_triggered();

    void on_actWidget_triggered();

    void on_actMainWindowInsite_triggered();

    void on_actMainWindow_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override; // 绘制主窗口背景图片
};
#endif // MAINWINDOW_H
