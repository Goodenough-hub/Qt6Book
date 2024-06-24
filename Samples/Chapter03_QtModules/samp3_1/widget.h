#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "TPerson.h"
#include <QMetaProperty>
#include <QMetaClassInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    TPerson *boy;
    TPerson *girl;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_btnClean_clicked();

    void on_btnBoyInc_clicked();

    void on_btnGirlInc_clicked();

    void do_ageChanged(int value);
    void do_spinChanged(int arg1);
    void on_btnMeta_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
