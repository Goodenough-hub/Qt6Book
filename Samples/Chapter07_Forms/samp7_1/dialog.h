#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QProgressDialog>
#include <QElapsedTimer>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnOpen_clicked();

    void on_btnClear_clicked();

    void on_btnOpenMulti_clicked();

    void on_btnSave_clicked();

    void on_btnSelDir_clicked();

    void on_btnColor_clicked();

    void on_btnFont_clicked();

    void on_btnProgress_clicked();

    void do_progress_canceled(); // 与进度对话框canceled()信号相关联的函数

    void on_btnInputString_clicked();

    void on_btnInputInt_clicked();

    void on_btnInputFloat_clicked();

    void on_btnInputItem_clicked();

    void on_btnMsInformation_clicked();

    void on_btnMsgWarning_clicked();

    void on_btnMsgCritical_clicked();

    void on_btnMsgAbout_clicked();

    void on_btnMsQuestion_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
