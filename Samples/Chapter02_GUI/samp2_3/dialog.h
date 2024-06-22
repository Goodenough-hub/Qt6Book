#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT
private:

    // 3个复选框
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;

    // 3个单选按钮
    QRadioButton *radioBlack;
    QRadioButton *radioRed;
    QRadioButton *radioBlue;

    // 3个按钮
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    // 文本框
    QPlainTextEdit *txtEdit;

    // ui创建与初始化
    void iniUI();

    // 初始化信号与槽的连接
    void iniSignalSlots();
private slots:
    void do_chkBoxUnder(bool checked);
    void do_chkBoxItalic(bool checked);
    void do_chkBoxBold(bool checked);
    void do_setFontColor();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
