#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildUI(); // 动态创建界面组件
    buildSignalSlots(); // 为动态创建的组件关联信号与槽
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly); // 工具按钮只显示图标
    this->setCentralWidget(ui->plainTextEdit); // plainTextEdit填满工作区
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildUI()
{
    // 创建状态栏上的组件
    labFile = new QLabel(this); // 用于显示当前文件名
    labFile->setMinimumWidth(150);
    labFile->setText("文件名：");
    ui->statusBar->addWidget(labFile); // 添加到状态栏

    // 状态栏上的进度条
    progressBar1 = new QProgressBar(this);
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->plainTextEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1);

    // 用于显示字体名称
    labInfo = new QLabel(this);
    labInfo->setText("选择字体名称：");
    ui->statusBar->addWidget(labInfo);

    // 为汉语、英语创建ActionGroup，实现互斥选择
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actLang_CN);
    actionGroup->addAction(ui->actLang_EN);
    actionGroup->setExclusive(true);
    ui->actLang_CN->setChecked(true);

    // 创建工具栏上无法可视化的一些组件
    spinFontSize = new QSpinBox(this);
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->plainTextEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(spinFontSize);

    comboFontName = new QFontComboBox(this);
    comboFontName->setMinimumWidth(150);
    ui->toolBar->addWidget(comboFontName);
    ui->toolBar->addAction(ui->actClose);
}

void MainWindow::buildSignalSlots()
{
    connect(spinFontSize, SIGNAL(valueChanged(int)), this, SLOT(do_fontSize_changed(int)));
    connect(comboFontName, &QFontComboBox::currentFontChanged, this, &MainWindow::do_fontSelected);
}

void MainWindow::do_fontSize_changed(int fontSize)
{
    // 设置字体大小的SpinBox
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFontPointSize(fontSize);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(fontSize);
}

void MainWindow::do_fontSelected(const QFont &font)
{
    // 选择字体的FontComboBox
    labInfo->setText("字体名称：" + font.family()); // 状态栏上显示
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFont(font);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFont_Bold_triggered(bool checked)
{
    // 粗体
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    if(checked)
    {
        fmt.setFontWeight(QFont::Bold);
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}



void MainWindow::on_actFont_Italic_triggered(bool checked)
{
    // 斜体
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFont_Underline_triggered(bool checked)
{
    // 下划线
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actFile_Save_triggered(bool checked)
{
    // 表示已经保存过了，改变修改状态
    ui->plainTextEdit->document()->setModified(false);
    labFile->setText("文件已经保存");
}


void MainWindow::on_actSys_ToggleText_triggered(bool checked)
{
    // 是否显示工具按钮文字
    if(checked)
    {
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else
    {
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    }
}


void MainWindow::on_plainTextEdit_copyAvailable(bool b)
{
    // copyAvailable()信号的槽函数，更新3个Action的enabled状态
    // 当可以copy时（选择了编辑框中的文字），复制、剪切、粘贴三个ACtion处于enabled状态
    ui->actEdit_Copy->setEnabled(b);
    ui->actEdit_Cut->setEnabled(b);
    ui->actEdit_Paste->setEnabled(ui->plainTextEdit->canPaste());
}


void MainWindow::on_plainTextEdit_selectionChanged()
{
    // selectionChanged()信号的槽函数，更新3种字体样式的checked状态
    // 选中的文字发生变化时，检查选中文字的样式，更新粗体、斜体、下划线的checked状态
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    ui->actFont_Bold->setChecked(fmt.font().bold()); // 粗体
    ui->actFont_Italic->setChecked(fmt.fontItalic()); // 斜体
    ui->actFont_Underline->setChecked(fmt.fontUnderline()); // 下划线
}

