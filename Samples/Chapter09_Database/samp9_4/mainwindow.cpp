#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::openTable()
{
    tabModel = new QSqlRelationalTableModel(this, DB);
    tabModel->setTable("studInfo");
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); // 编辑策略
    tabModel->setSort(tabModel->fieldIndex("studID"), Qt::AscendingOrder);
    selModel = new QItemSelectionModel(tabModel, this); // 创建选择模型
    connect(selModel, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionModel(selModel);
    // 设置字段标题
    tabModel->setHeaderData(tabModel->fieldIndex("studID"), Qt::Horizontal, "学号");
    tabModel->setHeaderData(tabModel->fieldIndex("name"), Qt::Horizontal, "姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("gender"), Qt::Horizontal, "性别");
    tabModel->setHeaderData(tabModel->fieldIndex("departID"), Qt::Horizontal, "学院");
    tabModel->setHeaderData(tabModel->fieldIndex("majorID"), Qt::Horizontal, "专业");
    // 设置编码字段的关系
    tabModel->setRelation(tabModel->fieldIndex("departID"), QSqlRelation("departments", "departID", "department")); // 学院
    tabModel->setRelation(tabModel->fieldIndex("majorID"), QSqlRelation("majors", "majorID", "major")); // 专业
    // 为外键字段设置默认代理
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    tabModel->select(); // 查询数据表的数据
    ui->actOpenDB->setEnabled(false);
    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actFields->setEnabled(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    ui->actSubmit->setEnabled(tabModel->isDirty()); // 有未保存的修改时可用
    ui->actRevert->setEnabled(tabModel->isDirty());
}

void MainWindow::on_actOpenDB_triggered()
{
    // 打开
    QString aFile = QFileDialog::getOpenFileName(this, "选择文件", "", "SQLite数据库(*.db3)");
    if(aFile.isEmpty())
        return;
    // 打开SQLite数据库
    DB = QSqlDatabase::addDatabase("QSQLITE"); // 添加 SQLITE 数据库驱动
    DB.setDatabaseName(aFile); // 设置数据库名称
    // DB.setHostName();
    // DB.setUserName();
    // DB.setPassword();
    if(!DB.open())
        QMessageBox::warning(this, "错误", "打开数据库失败");
    else
        openTable(); // 打开数据表
}


void MainWindow::on_actFields_triggered()
{
    // 获取字段列表
    QSqlRecord emptyRec = tabModel->record(); // 获取空记录，只有字段名
    QString str;
    for(int i = 0; i < emptyRec.count(); i ++)
        str = str + emptyRec.fieldName(i) + "\n";
    QMessageBox::information(this, "所有字段名", str);
}

