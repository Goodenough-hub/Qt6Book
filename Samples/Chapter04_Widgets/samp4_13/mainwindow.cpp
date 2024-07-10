#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::createItemARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    uint studID = 202105000; // 学号基数
    // 姓名
    QTableWidgetItem *item = new QTableWidgetItem(name, MainWindow::ctName); // type=ctName
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studID += rowNo; // 学号 = 基数 + 行号
    item->setData(Qt::UserRole, QVariant(studID)); // 设置studID为用户数据
    ui->tableinfo->setItem(rowNo, MainWindow::colName, item); // 为单元格设置item
    // 性别
    QIcon icon;
    if(sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item = new QTableWidgetItem(sex, MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled; // 性别 单元格不允许编辑
    item->setFlags(flags);
    ui->tableinfo->setItem(rowNo, MainWindow::colSex, item);
    //出生日期
    QString str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableinfo->setItem(rowNo, MainWindow::colBirth, item);
    //民族
    item = new QTableWidgetItem(nation, MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableinfo->setItem(rowNo, MainWindow::colNation, item);
    //是否党员
    item = new QTableWidgetItem("党员", MainWindow::ctPartM);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    // 党员 单元格不允许编辑，但是可以更改复选状态
    flags = Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackground(QBrush(Qt::yellow));
    ui->tableinfo->setItem(rowNo, MainWindow::colPartyM, item);
    // 分数
    str.setNum(score);
    item = new QTableWidgetItem(str, MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableinfo->setItem(rowNo, MainWindow::colScore, item);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 状态栏初始化
    labCellIndex = new QLabel("当前单元格坐标：", this);
    labCellIndex->setMinimumWidth(250);
    labCellType = new QLabel("当前单元格类型：", this);
    labCellType->setMinimumWidth(200);
    labStudID = new QLabel("学生：", this);
    labStudID->setMinimumWidth(200);
    // 添加到状态栏
    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudID);

    // 间隔行底色选择框默认勾选，则设置默认颜色错行。
    on_chkBoxRowColor_clicked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSetHeader_clicked()
{
    QStringList headerText;
    headerText<<"姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否党员";
    // ui->tableinfo->setHorizontalHeaderLabels(headerText); // 只设置标题
    ui->tableinfo->setColumnCount(headerText.size()); // 设置表格列数
    for(int i = 0; i < ui->tableinfo->columnCount(); i ++)
    {
        QTableWidgetItem *headerItem = new QTableWidgetItem(headerText.at(i)); // 创建item
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(11);
        headerItem->setForeground(QBrush(Qt::red)); // 设置文字颜色
        headerItem->setFont(font); // 设置字体
        ui->tableinfo->setHorizontalHeaderItem(i, headerItem); // 设置表头单元格的item
    }
}


void MainWindow::on_btnIniData_clicked()
{
    // qDebug("on_btnIniData_clicked 被点击");
    // qDebug("m_rows=%d", m_rows);
    QDate birth(2001, 4, 6); // 初始化日期
    //ui->tableinfo->clearContents(); // 只清除工作区，不清楚表头
    m_rows = ui->spinBoxRows->value();
    ui->tableinfo->setRowCount(m_rows); // 先设置总行数，否则不显示
    for(int i = 0; i < m_rows; i ++)
    {
        //qDebug("for循环");
        QString strName = QString("学生%1").arg(i);
        QString strSex = ((i % 2) == 0) ? "男":"女";
        bool isParty = ((i % 2) == 0) ? false:true;
        int score = QRandomGenerator::global()->bounded(60, 100); // 随机数范围为[60, 100)
        createItemARow(i, strName, strSex, birth, "汉族", isParty, score); // 为某一行创建items
        birth = birth.addDays(20); // 日期加20天
    }
}


void MainWindow::on_btnSetRows_clicked()
{
    m_rows = ui->spinBoxRows->value();
}


void MainWindow::on_tableinfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);
    QTableWidgetItem* item = ui->tableinfo->item(currentRow, currentColumn); // 获取item
    if(item == nullptr)
        return;

    labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行， %d 列", currentRow, currentColumn));
    int cellType = item->type();
    labCellType->setText(QString::asprintf("当前单元格类型：%d", cellType));

    item = ui->tableinfo->item(currentRow, MainWindow::colName); // 当前第一列的item
    uint ID = item->data(Qt::UserRole).toUInt();
    labStudID->setText(QString::asprintf("学生ID：%d", ID));
}


void MainWindow::on_btnInsertRow_clicked()
{
    // 在当前行后面插入行
    int cutRow = ui->tableinfo->currentRow();
    ui->tableinfo->insertRow(cutRow);
    createItemARow(cutRow, "新学生", "男", QDate::fromString("2002-10-1", "yyyy-MM-d"), "苗族", true, 80);
}


void MainWindow::on_btnAddRow_clicked()
{
    // 在最后一行添加行
    int cutRow = ui->tableinfo->rowCount();
    ui->tableinfo->insertRow(cutRow);
    createItemARow(cutRow, "新生", "女", QDate::fromString("2002-12-1", "yyyy-MM-d"), "满族", true, 90);
}


void MainWindow::on_btnDelCurRow_clicked()
{
    // 删除当前行
    int cutRow = ui->tableinfo->currentRow();
    ui->tableinfo->removeRow(cutRow);
}


void MainWindow::on_btnResizeRows_clicked()
{
    ui->tableinfo->resizeRowsToContents();
}


void MainWindow::on_btnResizeColumns_clicked()
{
    ui->tableinfo->resizeColumnsToContents();
}


void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    if(checked)
        ui->tableinfo->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked); // 允许编辑，双击或获取焦点后点击可进入编辑状态
    else
        ui->tableinfo->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不允许编辑
}


void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    // 是否显示水平表头
    ui->tableinfo->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    // 是否显示垂直表头
    ui->tableinfo->verticalHeader()->setVisible(checked);
}


void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    // 行的底色交替采用不同颜色
    ui->tableinfo->setAlternatingRowColors(checked);
}


void MainWindow::on_rBtnSelectRow_clicked()
{
    // 选择方式：行选择
    ui->tableinfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_rBtnSelectItem_clicked()
{
    // 选择方式：单元格选择
    ui->tableinfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_btnReadToEdit_clicked()
{
    // 遍历表格，读取数据
    QTableWidgetItem *item;
    ui->plainTextEdit->clear();
    for(int i = 0; i < ui->tableinfo->rowCount(); i ++)
    {
        QString str = QString::asprintf("第 %d 行：", i + 1);
        for(int j = 0; j < ui->tableinfo->columnCount(); j ++)
        {
            item = ui->tableinfo->item(i, j); // 获取单元格的item
            str = str + item->text() + " "; // 字符串拼接
        }
        item = ui->tableinfo->item(i, colPartyM); // 最后一列
        if(item->checkState() == Qt::Checked)
            str = str + "党员";
        else
            str = str + "群众";
        ui->plainTextEdit->appendPlainText(str);
    }
}

