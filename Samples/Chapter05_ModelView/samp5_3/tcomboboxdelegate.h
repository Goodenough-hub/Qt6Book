#ifndef TCOMBOBOXDELEGATE_H
#define TCOMBOBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class TComboBoxDelegate : public QStyledItemDelegate
{
private:
    QStringList m_itemList; // 选项列表
    bool m_editable; // 是否可编辑
public:
    explicit TComboBoxDelegate(QObject *parent = nullptr);
    void setItems(QStringList items, bool editable); // 初始化设置列表，是否可编辑

    // 自定义代理必须重现实现以下4个函数
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const; // 创建用于编辑模型数据的组件
    void setEditorData(QWidget *editor, const QModelIndex &index) const; // 从数据模型获取项的角色的数据，然后将其设置为代理编辑器上显示的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const; // 将代理编辑器里的输入数据保存到数据模型的项里
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const; // 为组件设置合适的大小
};

#endif // TCOMBOBOXDELEGATE_H
