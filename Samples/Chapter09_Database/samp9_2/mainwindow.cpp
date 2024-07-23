#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::selectData()
{
    // 1. 创建数据模型，打开数据表
    qryModel = new QSqlTableModel(this, DB); // 数据模型
    qryModel->setQuery("SELECT EmpNo, Gender, Birthday, Province, DepartMent, Salary FROM employee ORDER BY empNo");
    if(qryModel->lastError().isValid())
    {
        QMessageBox::critical(this, "错误", "数据表查询错误，错误信息\n" + qryModel->lastError().text());
        return ;
    }
    ui->statusBar->showMessage(QString("记录条数：%1").arg(qryModel->rowCount()));

    // 2. 设置字段显示标题
    QSqlRecord rec = qryModel->record(); // 获取一条空记录，为了获取字段序号
    qryModel->setHeaderData(rec.indexOf("empNo"), Qt::Horizontal, "工号");
    qryModel->setHeaderData(rec.indexOf("Name"), Qt::Horizontal, "姓名");
    qryModel->setHeaderData(rec.indexOf("Gender"), Qt::Horizontal, "性别");
    qryModel->setHeaderData(rec.indexOf("Birthday"), Qt::Horizontal, "出生日期");
    qryModel->setHeaderData(rec.indexOf("Province"), Qt::Horizontal, "省份");
    qryModel->setHeaderData(rec.indexOf("Department"), Qt::Horizontal, "部门");
    qryModel->setHeaderData(rec.indexOf("Salary"), Qt::Horizontal, "工资");

    // 3. 创建选择模型
    selModel = new QItemSelectionModel(qryModel, this);
    // 当前行变化时，selModel发射currentRowChanged()信号
    connect(selModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::do_currentRowChanged);

    // 4. 模型/视图结构
    ui->tableView->setModel(qryModel); // 设置数据模型
    ui->tableView->setSelectionModel(selModel); // 设置选择模型


    // 5. 创建界面组件与模型的字段的数据映射
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(qryModel); // 设置数据模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    // 界面组件与模型的具体字段的映射
    dataMapper->addMapping(ui->dbSpinEmpNo, rec.indexOf("empNo"));
    dataMapper->addMapping(ui->dbEditName, rec.indexOf("Name"));
    dataMapper->addMapping(ui->dbComboSex, rec.indexOf("Gender"));
    dataMapper->addMapping(ui->dbEditBirth, rec.indexOf("Birthday"));
    dataMapper->addMapping(ui->dbComboProvince, rec.indexOf("Province"));
    dataMapper->addMapping(ui->dbComboDep, rec.indexOf("Department"));
    dataMapper->addMapping(ui->dbSpinSalary, rec.indexOf("Salary"));
    dataMapper->addMapping(ui->dbEditMemo, rec.indexOf("Memo"));
    dataMapper->toFirst(); // 移动到首记录
    ui->actOpenDB->setEnabled(false);
}

void MainWindow::refreshTableView()
{
    // 刷新tableView的当前行
    int index = dataMapper->currentIndex(); // dataMapper的当前行号
    QModelIndex curIndex = qryModel->index(index, 0); // 为当前行创建模型索引
    selModel->clearSelection();
    selModel->setCurrentIndex(curIndex, QItemSelectionModel::Select); // 设置当前行
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->splitter);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单行选择，不能按住ctrl多选
    ui->tableView->setAlternatingRowColors(true); // 设置交替颜色
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 从当前记录里提取Photo字段的内容，再将图片显示出来
    Q_UNUSED(previous);
    if(!current.isValid())
    {
        ui->dbLabPhoto->clear(); // 清除图片
        ui->dbEditMemo->clear();
        return;
    }
    dataMapper->setCurrentModelIndex(current); // 设置当前行

    bool first = (current.row() == 0); // 是否是首记录
    bool last = (current.row() == qryModel->rowCount() - 1); // 是否是尾记录
    // 更新使能状态
    ui->actRecFirst->setEnabled(!first);
    ui->actRecPrevious->setEnabled(!first);
    ui->actRecNext->setEnabled(!last);
    ui->actRecLast->setEnabled(!last);

    int curRecNo = selModel->currentIndex().row();
    QSqlRecord curRec = qryModel->record(curRecNo); // 获取当前记录
    int empNo = curRec.value("EmpNo").toInt(); // 主键字段
    QSqlQuery query; // 根据EmpNo查询Memo和Photo字段数据
    query.prepare("SELECT EmpNo, Memo, Photo FROM employee WHERE EmpNo = :ID");
    query.bindValue(":ID", empNo);
    query.exec();
    query.first();

    QVariant va = query.value("Photo");
    if(!va.isValid())
        ui->dbLabPhoto->clear();
    else
    {
        QByteArray data = va.toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->size().width()));
    }
    QVariant va2 = query.value("Memo");
    ui->dbEditMemo->setPlainText(va2.toString());
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

    if(DB.open())
        selectData();
    else
        QMessageBox::warning(this, "错误", "打开数据库失败");
}


void MainWindow::on_actRecAppend_triggered()
{
    // 添加一条记录

}


void MainWindow::on_actRecInsert_triggered()
{
    // 插入一条数据
}


void MainWindow::on_actRecDelete_triggered()
{
    // 删除当前记录
}


void MainWindow::on_actSubmit_triggered()
{
    // 保存修改
}


void MainWindow::on_actRevert_triggered()
{
    // 取消修改
}


void MainWindow::on_actPhoto_triggered()
{
    // 设置图片
}


void MainWindow::on_actPhotoClear_triggered()
{
    // 清除照片
}


void MainWindow::on_actScan_triggered()
{
    // 涨工资，记录遍历
}


void MainWindow::on_actRecFirst_triggered()
{
    // 首记录
    dataMapper->toFirst();
    refreshTableView();
}


void MainWindow::on_actRecPrevious_triggered()
{
    // 前一记录
    dataMapper->toPrevious();
    refreshTableView();
}


void MainWindow::on_actRecNext_triggered()
{
    // 后一记录
    dataMapper->toNext();
    refreshTableView();
}


void MainWindow::on_actRecLast_triggered()
{
    // 尾记录
    dataMapper->toLast();
    refreshTableView();
}

