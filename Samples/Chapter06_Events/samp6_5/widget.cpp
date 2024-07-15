#include "widget.h"
#include "./ui_widget.h"

void Widget::refreshToUI(QGroupBox *curGroupBox)
{
    ui->chkBoxAcceptDrops->setChecked(m_itemView->acceptDrops());
    ui->chkBoxDragEnabled->setChecked(m_itemView->dragEnabled());

    ui->comboMode->setCurrentIndex((int)m_itemView->dragDropMode());
    int index = getDropActionIndex(m_itemView->defaultDropAction());
    ui->comboDefaultAction->setCurrentIndex(index);

    QFont font = ui->groupBox_3->font();
    font.setBold(false);
    ui->groupBox_3->setFont(font);
    ui->groupBox_4->setFont(font);
    ui->groupBox_6->setFont(font);
    ui->groupBox_7->setFont(font);

    font.setBold(true);
    curGroupBox->setFont(font);
}

int Widget::getDropActionIndex(Qt::DropAction actionType)
{
    /*CopyAction = 0x1,
    MoveAction = 0x2,
    LinkAction = 0x4,
    ActionMask = 0xff,
    TargetMoveAction = 0x8002,
    Qt::IgnoreAction = 0x0*/
    switch(actionType)
    {
    case Qt::CopyAction: return 0;
    case Qt::MoveAction: return 1;
    case Qt::LinkAction: return 2;
    case Qt::ActionMask: return 3;
    default: return 0;
    }
}

Qt::DropAction Widget::getDropActionType(int index)
{
    switch(index)
    {
    case 0:
        return Qt::CopyAction;
    case 1:
        return Qt::MoveAction;
    case 2:
        return Qt::LinkAction;
    case 3:
        return Qt::IgnoreAction;
    default:
        return Qt::CopyAction;
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 安装事件过滤器，由窗口处理四个项数据组件的事件
    ui->listWidget->installEventFilter(this);
    ui->listWidget_2->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);

    m_itemView = ui->listWidget;
    refreshToUI(ui->groupBox_3);

    //设置widget自动调整大小
    resizeEvent(nullptr);

    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);

    ui->listWidget_2->setAcceptDrops(true);
    ui->listWidget_2->setDragEnabled(true);
    ui->listWidget_2->setDefaultDropAction(Qt::CopyAction);
    ui->listWidget_2->setDragDropMode(QAbstractItemView::DragDrop);

    ui->tableWidget->setAcceptDrops(true);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setDefaultDropAction(Qt::MoveAction);
    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);

    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::CopyAction);
    ui->treeWidget->setDragDropMode(QAbstractItemView::DragDrop);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    // 自动调整Widget的大小
    QSize sz1= ui->groupBox_3->size();
    QSize sz2= ui->groupBox_4->size();
    QSize sz3= ui->groupBox_6->size();
    QSize sz4= ui->groupBox_7->size();

    ui->listWidget->resize(sz1.width() - 20, sz1.height() - 25);
    ui->listWidget_2->resize(sz2.width() - 20, sz2.height() - 25);
    ui->treeWidget->resize(sz3.width() - 20, sz3.height() - 25);
    ui->tableWidget->resize(sz4.width() - 20, sz4.height() - 25);

    if(event != nullptr) event->accept();
}


void Widget::on_radioListWidget_clicked()
{
    m_itemView = ui->listWidget_2;
    refreshToUI(ui->groupBox_4);
}


void Widget::on_radioListSource_clicked()
{
    m_itemView = ui->listWidget;
    refreshToUI(ui->groupBox_3);
}


void Widget::on_radioTreeWidget_clicked()
{
    m_itemView = ui->treeWidget;
    refreshToUI(ui->groupBox_6);
}


void Widget::on_radioTableWidget_clicked()
{
    m_itemView = ui->tableWidget;
    refreshToUI(ui->groupBox_7);
}


void Widget::on_chkBoxAcceptDrops_clicked(bool checked)
{
    m_itemView->setAcceptDrops(checked);
}


void Widget::on_chkBoxDragEnabled_clicked(bool checked)
{
    m_itemView->setDragEnabled(checked);
}


void Widget::on_comboMode_currentIndexChanged(int index)
{
    m_itemView->setDragDropMode((QAbstractItemView::DragDropMode)index);
}


void Widget::on_comboDefaultAction_currentIndexChanged(int index)
{
    m_itemView->setDefaultDropAction(getDropActionType(index));
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() != QEvent::KeyPress) // 不是KetPress事件，退出
        return QWidget::eventFilter(watched, event);

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if(keyEvent->key() != Qt::Key_Delete) // 按下的不是Delete键，退出
        return QWidget::eventFilter(watched, event);

    if(watched == ui->listWidget)
    {
        QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    }
    else if(watched == ui->listWidget_2)
    {
        QListWidgetItem* item = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
        delete item;
    }
    else if(watched == ui->treeWidget)
    {
        QTreeWidgetItem* curItem = ui->treeWidget->currentItem();
        if(curItem->parent() != nullptr)
        {
            QTreeWidgetItem *parItem = curItem->parent();
            parItem->removeChild(curItem); // 通过父节点parItem删除curItem
        }
        else
        {
            int index = ui->treeWidget->indexOfTopLevelItem(curItem);
            ui->treeWidget->takeTopLevelItem(index);
        }
        delete curItem;
    }
    else if(watched == ui->tableWidget)
    {
        QTableWidgetItem *item = ui->tableWidget->takeItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn());
        delete item;
    }
    return true; // 表示事件已经被处理了
}

