#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_btnCLearList_clicked();

    void on_btnIni2_clicked();

    void on_comboBox_simple_currentTextChanged(const QString &arg1);

    void on_comboBox_city_currentIndexChanged(int index);

    void on_btnClearEdit_clicked();

    void on_chkboxEdit_clicked(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
