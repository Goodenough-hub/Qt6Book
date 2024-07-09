#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(colItem);
    item->setText(colItem, str);
    if(item->childCount() > 0) // 若有孩子
        for(int i = 0; i < item->childCount(); ++ i)
            changeItemCaption(item->child(i));
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString filename = item->data(colItem, Qt::UserRole).toString();
    labFileName->setText(filename);
    labNodeText->setText(item->text(colItem));
    m_pixmap.load(filename);
    ui->actZoomFitH->trigger();

    ui->actZoomFitH->setEnabled(true);
    ui->actZoomFitW->setEnabled(true);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actZoomRealSize->setEnabled(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->clear();

    QTreeWidgetItem *head = new QTreeWidgetItem();
    head->setText(colItem, "目录和文件");
    head->setText(colItemTye, "节点类型");
    head->setText(colDate, "最后的修改日期");

    // 设置对齐方式
    head->setTextAlignment(colItem, Qt::AlignHCenter | Qt::AlignVCenter);
    head->setTextAlignment(colItemTye, Qt::AlignHCenter | Qt::AlignVCenter);
    head->setTextAlignment(colDate, Qt::AlignHCenter | Qt::AlignVCenter);

    ui->treeWidget->setHeaderItem(head);

    // 添加根节点
    QIcon icon(":/images/icons/15.ico");
    QTreeWidgetItem *topItem = new QTreeWidgetItem(itTopItem);
    topItem->setIcon(colItem, icon);
    topItem->setText(colItem, "图片");
    topItem->setText(colItemTye, "Top Item");
    topItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    topItem->setCheckState(colItem, Qt::Checked);
    ui->treeWidget->addTopLevelItem(topItem);

    // status Bar
    labNodeText = new QLabel("节点标题", this);
    labNodeText->setMinimumWidth(200);
    ui->statusbar->addWidget(labNodeText);

    spinRatio = new QSpinBox(this);
    spinRatio->setRange(0, 200);
    spinRatio->setValue(100);
    spinRatio->setSuffix(" %");
    spinRatio->setReadOnly(true);
    spinRatio->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->statusbar->addPermanentWidget(spinRatio);

    labFileName = new QLabel("文件名", this);
    ui->statusbar->addPermanentWidget(labFileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actAddFolder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory();
    if(dir.isEmpty()) return;

    QTreeWidgetItem *parItem = ui->treeWidget->currentItem();
    if(parItem==nullptr) return;

    if(parItem->type() != itImageItem)
    {
        int cnt = dir.length();
        int i = dir.lastIndexOf("/");
        QString nodeName = dir.right(cnt - i - 1);

        QTreeWidgetItem *item = new QTreeWidgetItem(itGroupItem);
        QIcon icon(":/images/icons/open3.bmp");
        item->setIcon(colItem, icon);
        item->setText(colItem, nodeName);
        item->setText(colItemTye, "Group Item");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
        item->setCheckState(colItem, Qt::Checked);
        item->setData(colItem, Qt::UserRole, QVariant(dir));
        parItem->addChild(item);
    }
    parItem->setExpanded(true);
}


void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "选择文件", "", "Images(*.jpg)");
    if(files.isEmpty()) return;

    QTreeWidgetItem *parItem, *item;
    item = ui->treeWidget->currentItem();
    if(item==nullptr) item=ui->treeWidget->topLevelItem(0);

    if(item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem=item;

    for(int i = 0; i < files.size(); ++ i)
    {
        QString fileName = files.at(i);
        QIcon icon(":/images/icons/31.ico");
        QFileInfo fileInfo(fileName);
        QString NodeText = fileInfo.fileName();
        QDateTime dateTime = fileInfo.lastModified();

        QTreeWidgetItem *item = new QTreeWidgetItem(itImageItem);
        item->setIcon(colItem, icon);
        item->setText(colItem, NodeText);
        item->setText(colItemTye, "Image Item");
        item->setText(colDate, dateTime.toString("yyyy-MM-dd"));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
        item->setCheckState(colItem, Qt::Checked);
        item->setData(colItem, Qt::UserRole, QVariant(fileName));
        parItem->addChild(item);
    }
    parItem->setExpanded(true);
}


void MainWindow::on_actDeleteItem_triggered()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item==nullptr) return;

    QTreeWidgetItem *parItem = item->parent();
    parItem->removeChild(item);
}


void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current==nullptr || current==previous) return;

    switch (current->type()) {
    case itTopItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddFolder->setEnabled(true);
        ui->actDeleteItem->setEnabled(false);
        break;
    case itGroupItem:
        ui->actAddFiles->setEnabled(true);
        ui->actAddFolder->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;
    case itImageItem:
        // displayImage(current);
        displayImage(current);
        ui->actAddFiles->setEnabled(false);
        ui->actAddFolder->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;
    }
}


void MainWindow::on_actSacnItems_triggered()
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++ i)
    {
        changeItemCaption(ui->treeWidget->topLevelItem(i));
    }
}


void MainWindow::on_actZoomFitW_triggered()
{
    int w = ui->scrollArea->width()-30;
    int realw = m_pixmap.width();
    m_ratio = float(w) / realw;

    spinRatio->setValue(m_ratio * 100);

    QPixmap pix = m_pixmap.scaledToWidth(w - 30);
    ui->labelPic->setPixmap(pix);
}


void MainWindow::on_actZoomFitH_triggered()
{
    int h = ui->scrollArea->height()-30;
    int realh = m_pixmap.height();
    m_ratio = float(h) / realh;

    spinRatio->setValue(m_ratio * 100);

    QPixmap pix = m_pixmap.scaledToHeight(h - 30);
    ui->labelPic->setPixmap(pix);
}


void MainWindow::on_actZoomRealSize_triggered()
{
    ui->labelPic->setPixmap(m_pixmap);
    m_ratio = 1;
    spinRatio->setValue(100);
}


void MainWindow::on_actZoomIn_triggered()
{
    m_ratio *= 1.2;
    int w = m_ratio * m_pixmap.width();
    int h = m_ratio * m_pixmap.height();
    ui->labelPic->setPixmap(m_pixmap.scaled(w, h));
    spinRatio->setValue(100 * m_ratio);
}


void MainWindow::on_actZoomOut_triggered()
{
    m_ratio *= 0.8;
    int w = m_ratio * m_pixmap.width();
    int h = m_ratio * m_pixmap.height();
    ui->labelPic->setPixmap(m_pixmap.scaled(w, h));
    spinRatio->setValue(100 * m_ratio);
}


void MainWindow::on_actDockVisible_triggered(bool checked)
{
    ui->dockWidget->setVisible(true);
}


void MainWindow::on_actDockerFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}


void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}


void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockerFloat->setChecked(topLevel);
}

