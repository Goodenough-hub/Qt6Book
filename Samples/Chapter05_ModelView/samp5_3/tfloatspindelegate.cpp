#include "tfloatspindelegate.h"


TFloatSpinDelegate::TFloatSpinDelegate(QObject *parent)
{

}

QWidget *TFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent); // 新建代理编辑器
    editor->setFrame(false); // 组件的属性设置
    editor->setMinimum(0);
    editor->setMaximum(20000);
    editor->setDecimals(2); // 显示两位小数
    return editor;
}

void TFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    float value = index.model()->data(index, Qt::EditRole).toFloat(); // 从模型获取数据
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value); // 设置为代理编辑器的值
}

void TFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    float value = spinBox->value();
    QString str = QString::asprintf("%.2f", value);
    model->setData(index, str, Qt::EditRole); // 保存到数据模型
}

void TFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect); // 设置组件的大小
}
