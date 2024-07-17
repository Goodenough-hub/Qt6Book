#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false); // 隐藏tabWidget
    ui->tabWidget->clear(); // 清除所有页面
    ui->tabWidget->setTabsClosable(true); // 各页面有关闭按钮，可被关闭
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized); // 窗口最大化显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_changeTabTitle(QString title)
{
    // 自定义槽函数，用于设置tabWidget当前页的标题
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index, title);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // 获取窗口的画笔
    painter.drawPixmap(0, ui->maintoolBar->height(), this->width(), this->height() - ui->maintoolBar->height() - ui->statusbar->height(), QPixmap(":/Pics/images/back2.jpg"));
    event->accept();

}

void MainWindow::on_actWidgetInsite_triggered()
{
    TFormDoc *formDoc = new TFormDoc(this); // 指定主窗口为父容器
    formDoc->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    int cur = ui->tabWidget->addTab(formDoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
    connect(formDoc, &TFormDoc::titleChanged, this, &MainWindow::do_changeTabTitle);
}


void MainWindow::on_actWidget_triggered()
{
    TFormDoc *formDoc = new TFormDoc(); // 不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    formDoc->setWindowTitle("基于QWdiget的窗口，无父窗口，关闭时删除");
    formDoc->setWindowFlag(Qt::Window, true); // 设置window标志
    formDoc->setWindowOpacity(0.9); // 设置透明度
    formDoc->show(); // 显示为单独的窗口
}


void MainWindow::on_actMainWindowInsite_triggered()
{
    TFormTable *formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    int cur = ui->tabWidget->addTab(formTable, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actMainWindow_triggered()
{
    TFormTable* formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("基于QMainWindow的窗口");
    formTable->statusBar(); // 如果没有状态栏就创建状态栏
    formTable->show();
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index < 0)
        return;
    QWidget *aForm = ui->tabWidget->widget(index); // 获取分页上的widget
    aForm->close(); // 关闭嵌入式窗口
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool en = ui->tabWidget->count() > 0; // 是否还有页面
    ui->tabWidget->setVisible(en);
}

