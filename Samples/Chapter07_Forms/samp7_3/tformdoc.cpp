#include "tformdoc.h"
#include "ui_tformdoc.h"

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TFormDoc)
{
    ui->setupUi(this);
    // 使用设计好的Action工具栏
    QToolBar* locToolBar = new QToolBar("文档", this); // 创建工具栏
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addAction(ui->actClose);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    // 设计布局
    QVBoxLayout* Layout = new QVBoxLayout();
    Layout->addWidget(locToolBar); // 设置工具栏和plainTextEdit垂直布局
    Layout->addWidget(ui->plainTextEdit);
    Layout->setContentsMargins(2, 2, 2, 2); // 减小边框的宽度
    this->setLayout(Layout);
}

TFormDoc::~TFormDoc()
{
    delete ui;
}

void TFormDoc::loadFromFile(QString &FileName)
{
    // 加载文件内容
    QFile aFile(FileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text)) // 以只读文本方式打开文件
    {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str = aStream.readLine(); // 读取文件的一行
            ui->plainTextEdit->appendPlainText(str); // 添加到文本框显示
        }
        aFile.close();

        QFileInfo fileInfo(FileName); // 获取文件信息
        QString shortName = fileInfo.fileName(); // 不带有路径的文件名
        this->setWindowTitle(shortName);
        emit titleChanged(shortName); // 发射信号，以文件名作为参数
    }
}

void TFormDoc::on_actOpen_triggered()
{
    // 打开文件
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");

    if(aFileName.isEmpty())
        return;
    loadFromFile(aFileName);
}


void TFormDoc::on_actFont_triggered()
{
    // 设置字体
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

