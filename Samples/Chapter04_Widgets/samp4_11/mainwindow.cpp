#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tBtnListInit->setDefaultAction(ui->actListInit);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);

    ui->tBtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);

    QMenu *MenuSelection = new QMenu();
    MenuSelection->addAction(ui->actSelAll);
    MenuSelection->addAction(ui->actSelNone);
    MenuSelection->addAction(ui->actSelInvs);

    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setMenu(MenuSelection);

    // 工具栏上的项选择
    QToolButton *aBtn = new QToolButton(this);
    aBtn->setText("选择项目");
    aBtn->setIcon(QIcon(":/images/icons/414.bmp"));
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setMenu(MenuSelection);
    ui->toolBar->addWidget(aBtn);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);

    ui->chkBoxSorting->setCheckState(Qt::Unchecked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actListInit_triggered()
{
    // 初始化列表
    QListWidgetItem *aItem;
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isCheckable();

    ui->listWidget->clear();
    for(int i = 0; i < 10; i ++)
    {
        QString str = QString("Item %1").arg(i);
        aItem = new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);

        if(chk)
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

        ui->listWidget->addItem(aItem);
    }
}


void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_actListInsert_triggered()
{
    QIcon aIcon(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isCheckable();


    QString str = QString("Item Inserted");
    QListWidgetItem *aItem = new QListWidgetItem();
    aItem->setText(str);
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);

    if(chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

    ui->listWidget->insertItem(ui->listWidget->currentRow() + 1,aItem);

}


void MainWindow::on_actListAppend_triggered()
{
    QIcon aIcon(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isCheckable();


    QString str = QString("Item Appended");
    QListWidgetItem *aItem = new QListWidgetItem();
    aItem->setText(str);
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);

    if(chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

    ui->listWidget->addItem(aItem);
}


void MainWindow::on_actListDelete_triggered()
{
    int row = ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(row);
}


void MainWindow::on_actSelAll_triggered()
{
    int count = ui->listWidget->count();
    for(int i = 0; i < count; i ++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_tBtnSelNone_triggered()
{
    int count = ui->listWidget->count();
    for(int i = 0; i < count; i ++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_tBtnSelInvs_triggered()
{
    int count = ui->listWidget->count();
    for(int i = 0; i < count; i ++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        if(aItem->checkState() == Qt::Checked)
        {
            aItem->setCheckState(Qt::Unchecked);
        }
        else aItem->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current != NULL)
    {
        if(previous== NULL)
            str = "当前项：" + current->text();
        else
            str = "前一项：" + previous->text() + "; 当前项：" + current->text();
    }
    ui->editCurItemText->setText(str);

    // ToolBox中信号发射时机
    ui->plainTextEdit->appendPlainText("currentItemChanged()信号被发射");
}


void MainWindow::on_chkBoxSorting_clicked(bool checked)
{
    //ui->listWidget->setSortingEnabled(checked);
}


void MainWindow::on_tBtnSortAsc_clicked()
{
    if(ui->chkBoxSorting->checkState() == Qt::Checked)
        ui->listWidget->sortItems(Qt::AscendingOrder);
}


void MainWindow::on_tBtnSortDec_clicked()
{
    if(ui->chkBoxSorting->checkState() == Qt::Checked)
        ui->listWidget->sortItems(Qt::DescendingOrder);
}


void MainWindow::on_tBtnClearText_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_tBtnAddLine_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemDoubleClicked：" + item->text());
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menuList = new QMenu();
    menuList->addAction(ui->actListInit);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);
    menuList->exec(QCursor::pos());
    delete menuList;
}

