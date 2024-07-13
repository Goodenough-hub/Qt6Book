#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 将分割布局垂直方向尺寸策略设置为扩展的
    ui->splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //构建模型/视图结构
    m_model = new QFileSystemModel(this);
    m_model->setRootPath(QDir::currentPath()); // 设置根目录
    ui->treeView->setModel(m_model); // 设置数据模型
    ui->listView->setModel(m_model); // 设置数据模型
    ui->tableView->setModel(m_model); // 设置数据模型
    // 信号与槽关联，点击treeView的一个节点时，此节点设置为listView和tableView的根节点
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->listView, SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->tableView, SLOT(setRootIndex(QModelIndex)));

    // 显示状态栏信息
    labPath = new QLabel("CurrentFilePath:", this);
    ui->statusBar->addWidget(labPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(m_model->isDir(index)); // 是不是文件夹
    labPath->setText(m_model->filePath(index)); // 完整路径或文件名
    ui->labType->setText(m_model->type(index)); // 类型描述文字
    ui->labFileName->setText(m_model->fileName(index)); // 文件名或最后一级文件夹名称
    int sz = m_model->size(index) /1024; // 目录大小是0
    if(sz < 1024)
        ui->labFileFileSize->setText(QString("%1 KB").arg(sz));
    else
        ui->labFileFileSize->setText(QString::asprintf("%.1f MB", sz / 1024.0));
}


void MainWindow::on_actSetRootDir_triggered()
{
    // 设置根目录
    QString dir = QFileDialog::getExistingDirectory(this, "选择目录", QDir::currentPath());
    if(!dir.isEmpty())
    {
        m_model->setRootPath(dir);
        ui->treeView->setRootIndex(m_model->index(dir)); // 设置根目录
    }
}


void MainWindow::on_radioShowAll_clicked()
{
    // 显示目录和文件
    ui->groupBox->setEnabled(true);
    m_model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
}


void MainWindow::on_radioShowOnlyDir_clicked()
{
    // 只显示目录
    //ui->groupBox->setEnabled(false);
    m_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot); // 不列出文件
}


void MainWindow::on_chkBoxEnableFilter_clicked(bool checked)
{
    // 文件名过滤
    m_model->setNameFilterDisables(!checked);
    ui->comboBox->setEnabled(checked);
    ui->btnApplyFilters->setEnabled(checked);
}


void MainWindow::on_btnApplyFilters_clicked()
{
    // 应用
    QString flts = ui->comboBox->currentText().trimmed();
    QStringList filter = flts.split(";", Qt::SkipEmptyParts);
    m_model->setNameFilters(filter);
}

