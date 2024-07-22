#include "tcomboboxdelegate.h"

TComboBoxDelegate::TComboBoxDelegate(QObject *parent)
{

}

void TComboBoxDelegate::setItems(QStringList items, bool editable)
{
    m_itemList = items;
    m_editable = editable;
}

QWidget *TComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(m_editable);
    for(int i = 0; i < m_itemList.count(); i ++)
        editor->addItem(m_itemList.at(i));
    return editor;
}

void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);
}

void TComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void TComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
