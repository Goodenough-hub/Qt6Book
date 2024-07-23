#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::selectData()
{
    // 创建数据模型，打开数据表
    qryModel = new QSqlTableModel(this, DB); // 数据模型
    // 创建选择模型
    selModel = new QItemSelectionModel(qryModel, this);
    ui->tableView->setModel(qryModel); // 设置数据模型
    ui->tableView->setSelectionModel(selModel); // 设置选择模型

    qryModel->setQuery("SELECT EmpNo, Name, Gender, Birthday, Province, DepartMent, Salary FROM employee ORDER BY empNo");
    if(qryModel->lastError().isValid())
    {
        QMessageBox::critical(this, "错误", "数据表查询错误，错误信息\n" + qryModel->lastError().text());
        return ;
    }

    // 设置字段显示标题
    QSqlRecord rec = qryModel->record(); // 获取一条空记录，为了获取字段序号
    qryModel->setHeaderData(rec.indexOf("empNo"), Qt::Horizontal, "工号");
    qryModel->setHeaderData(rec.indexOf("Name"), Qt::Horizontal, "姓名");
    qryModel->setHeaderData(rec.indexOf("Gender"), Qt::Horizontal, "性别");
    qryModel->setHeaderData(rec.indexOf("Birthday"), Qt::Horizontal, "出生日期");
    qryModel->setHeaderData(rec.indexOf("Province"), Qt::Horizontal, "省份");
    qryModel->setHeaderData(rec.indexOf("Department"), Qt::Horizontal, "部门");
    qryModel->setHeaderData(rec.indexOf("Salary"), Qt::Horizontal, "工资");

    ui->actOpenDB->setEnabled(false);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actRecEdit->setEnabled(true);
    ui->actScan->setEnabled(true);
}

void MainWindow::updateRecord(int recNo)
{
    // 更新一条记录
    QSqlRecord curRec = qryModel->record(recNo); // 获取数据模型的一条记录
    int empNo = curRec.value("EmpNo").toInt(); // 获取EmpNo字段的值
    QSqlQuery query;
    query.prepare("SELECT * FROM employee WHERE EmpNo = :ID");
    query.bindValue(":ID", empNo);
    query.exec();
    query.first();
    if(!query.isValid()) // 无效记录
        return;

    curRec = query.record(); // 获取当前记录
    TDialogData *dataDialog = new TDialogData(this); // 创建对话框
    Qt::WindowFlags flags = dataDialog->windowFlags();
    dataDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); // 对话框固定大小
    dataDialog->setUpdateRecord(curRec); // 更新对话框的数据和界面

    int ret = dataDialog->exec();
    if(ret == QDialog::Accepted)
    {
        QSqlRecord recData = dataDialog->getRecordData(); // 获取对话框返回的记录
        query.prepare("UPDATE employee SET Name=:Name, Gender=:Gender, Birthday=:Birthday, Province=:Province, Department=:Department, Salary=:Salary, Memo=:Memo, Photo=:Photo WHERE EmpNo = :ID");
        query.bindValue(":Name", recData.value("Name"));
        query.bindValue(":Gender", recData.value("Gender"));
        query.bindValue("Birthday", recData.value("Birthday"));
        query.bindValue(":Province", recData.value("Province"));
        query.bindValue(":Department", recData.value("Department"));
        query.bindValue(":Salary", recData.value("Salary"));
        query.bindValue(":Memo", recData.value("Memo"));
        query.bindValue(":Photo", recData.value("Photo"));
        query.bindValue(":ID", empNo);
        if(!query.exec())
            QMessageBox::critical(this, "错误", "记录更新错误\n" + query.lastError().text());
        else
            qryModel->query().exec(); // 数据模型重新查询数据，更新tableView显示内容
    }
    delete dataDialog;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单行选择，不能按住ctrl多选
    ui->tableView->setAlternatingRowColors(true); // 设置交替颜色
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenDB_triggered()
{
    // 打开数据库
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
    QSqlQuery query;
    query.exec("SELECT * FROM employee WHERE EmpNo = -1"); // 查不出实际记录，只查询出字段信息
    QSqlRecord curRec = query.record(); // 获取当前记录，实际为空记录
    curRec.setValue("EmpNo", qryModel->rowCount() + 30000);

    TDialogData *dataDialog = new TDialogData(this); // 创建对话框
    Qt::WindowFlags flags = dataDialog->windowFlags();
    dataDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); // 对话框固定大小
    dataDialog->setInsertRecord(curRec); // 插入记录

    int ret = dataDialog->exec();
    if(ret == QDialog::Accepted)
    {
        QSqlRecord recData = dataDialog->getRecordData(); // 获取对话框返回的记录
        query.prepare("INSERT INTO employee (EmpNo, Name, Gender, Birthday, Province, Department, Salary, Memo, Photo) VALUES(:EmpNo, :Name, :Gender, :Birthday, :Province, :Department, :Salary, :Memo, :Photo)");
        query.bindValue(":EmpNo", recData.value("EmpNo"));
        query.bindValue(":Name", recData.value("Name"));
        query.bindValue(":Gender", recData.value("Gender"));
        query.bindValue("Birthday", recData.value("Birthday"));
        query.bindValue(":Province", recData.value("Province"));
        query.bindValue(":Department", recData.value("Department"));
        query.bindValue(":Salary", recData.value("Salary"));
        query.bindValue(":Memo", recData.value("Memo"));
        query.bindValue(":Photo", recData.value("Photo"));
        if(!query.exec())
            QMessageBox::critical(this, "错误", "插入记录错误\n" + query.lastError().text());
        else
        {
            QString sqlStr = qryModel->query().executedQuery(); // 运行过的SELECT语句
            qryModel->setQuery(sqlStr); // 重新查询数据
        }
    }
    delete dataDialog;
}


void MainWindow::on_actRecDelete_triggered()
{
    // 删除当前记录
    int curRecNo = selModel->currentIndex().row();
    QSqlRecord curRec = qryModel->record(curRecNo); // 获取当前记录
    if(curRec.isEmpty()) // 获取当前记录
        return;

    int empNo = curRec.value("EmpNo").toInt(); // 获取工号
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE EmpNo = :ID");
    query.bindValue(":ID", empNo);
    if(!query.exec())
        QMessageBox::critical(this, "错误", "删除记录出现错误\n" + query.lastError().text());
    else
    {
        QString sqlStr = qryModel->query().executedQuery(); // 运行过的SELECT语句
        qryModel->setQuery(sqlStr); // 重新查询数据
    }
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

    // 1. 遍历数据集并逐条更新记录数据
    // QSqlQuery qryUpdate; // 用于临时运行SQL语句
    // qryUpdate.prepare("UPDATE employee SET Salary=:Salary WHERE EmpNo=:ID");
    // QSqlQuery qryEmpList;
    // qryEmpList.setForwardOnly(true); // 设置为仅能前向移动，提高查询性能
    // qryEmpList.exec("SELECT empNo, Salary FROM employee ORDER BY empNo");
    // qryEmpList.first();
    // while(qryEmpList.isValid()) // 当前记录有效
    // {
    //     int empID = qryEmpList.value("empNo").toInt();
    //     float salary = 1000 + qryEmpList.value("Salary").toFloat();
    //     qryUpdate.bindValue(":ID", empID);
    //     qryUpdate.bindValue(":Salary", salary);
    //     qryUpdate.exec();
    //     qryEmpList.next(); // 移动到下一条记录
    // }
    // qryModel->query().exec(); // 数据模型重新查询数据，更新tableView的显示内容
    // QMessageBox::information(this, "提示", "涨工资数据计算完毕");

    // 2. 运行一条SQL语句
    QSqlQuery qryUpdate;
    qryUpdate.exec("UPDATE employee SET Salary=Salary+1000");
    qryModel->query().exec();
    QMessageBox::information(this, "提示", "涨工资数据计算完毕");
}


void MainWindow::on_actRecFirst_triggered()
{
    // 首记录
}


void MainWindow::on_actRecPrevious_triggered()
{
    // 前一记录
}


void MainWindow::on_actRecNext_triggered()
{
    // 后一记录
}


void MainWindow::on_actRecLast_triggered()
{
    // 尾记录
}


void MainWindow::on_actRecEdit_triggered()
{
    // 编辑当前记录
    int curRecNo = selModel->currentIndex().row();
    updateRecord(curRecNo);
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    // 在tableView上双击某条记录，编辑当前记录
    int curRecNo = index.row();
    updateRecord(curRecNo);
}

