#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tformdoc.h"
#include <QMdiSubWindow>
#include <QDir>
#include <QFileDialog>

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
    void on_actDoc_New_triggered();

    void on_actDoc_open_triggered();

    void on_actCloseAll_triggered();

    void on_actCascade_triggered();

    void on_actTile_triggered();

    void on_actViewMode_triggered(bool checked);

    void on_actDoc_Save_triggered();

    void on_actCut_triggered();

    void on_actCopy_triggered();

    void on_actPaste_triggered();

    void on_actFont_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
