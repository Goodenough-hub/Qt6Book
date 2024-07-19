#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSaveFile>
#include <QException>
#include <QTextBlock>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool openByIO_Whole(const QString &aFileName);
    bool openByIO_Lines(const QString &aFileName);
    bool saveByIO_Whole(const QString &aFileName);
    bool saveByIO_Safe(const QString &aFileName);
    bool openByStream_Whole(const QString &aFileName);
    bool openByStream_Lines(const QString &aFileName);
    bool saveByStream_Safe(const QString &aFileName);
    bool saveByStream_Whole(const QString &aFileName);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_IODevice_triggered();

    void on_actSave_IODevice_triggered();

    void on_actionSave_TextSafe_triggered();

    void on_actOpen_TextStream_triggered();

    void on_actionSave_TextStream_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
