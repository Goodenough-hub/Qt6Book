#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QActionGroup>

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
private:
    QLabel *labFile; // 添加到状态栏里
    QLabel *labInfo; // 添加到状态栏里
    QProgressBar *progressBar1; // 进度条，添加到状态栏上
    QSpinBox *spinFontSize; // 字体大小，添加到工具栏上
    QFontComboBox *comboFontName; // 字体名称，添加到工具栏上
    QActionGroup *actionGroup; // Action分组，用于“汉语”和"English"两个工具按钮的互斥选择
    void buildUI(); // 以代码化方式创建UI
    void buildSignalSlots(); // 手动关联信号与槽
private slots:
    void do_fontSize_changed(int fontSize);
    void do_fontSelected(const QFont &font);
    void on_actFont_Bold_triggered(bool checked);

    void on_actFont_Italic_triggered(bool checked);

    void on_actFont_Underline_triggered(bool checked);

    void on_actFile_Save_triggered(bool checked);

    void on_actSys_ToggleText_triggered(bool checked);

    void on_plainTextEdit_copyAvailable(bool b);

    void on_plainTextEdit_selectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
