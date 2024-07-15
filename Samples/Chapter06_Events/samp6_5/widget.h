#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QAbstractItemView>
#include <QGroupBox>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    QAbstractItemView *m_itemView=nullptr; // 用这个指针指向当前设置的view
    void refreshToUI(QGroupBox *curGroupBox); // 将组件的属性显示到界面上

    int getDropActionIndex(Qt::DropAction actionType);
    Qt::DropAction getDropActionType(int index);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_radioListWidget_clicked();
    void on_radioListSource_clicked();
    void on_radioTreeWidget_clicked();
    void on_radioTableWidget_clicked();
    void on_chkBoxAcceptDrops_clicked(bool checked);
    void on_chkBoxDragEnabled_clicked(bool checked);
    void on_comboMode_currentIndexChanged(int index);
    void on_comboDefaultAction_currentIndexChanged(int index);

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // WIDGET_H
