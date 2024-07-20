#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(false); // 禁用数据读写分组框
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnFile_triggered(QAction *arg1)
{

}


void MainWindow::on_btnFile_clicked()
{
    // 测试用文件
    QString curPath = QDir::currentPath();
    m_filename = QFileDialog::getOpenFileName(this, "选择一个文件", curPath, "流数据文件(*.stream)");

    if(!m_filename.isEmpty())
    {
        ui->editFilename->setText(m_filename);
        ui->groupBox->setEnabled(true);
        ui->actSaveALL->setEnabled(true);
        ui->actReadALL->setEnabled(true);
    }
}


template<class T>
void MainWindow::writeByStream(T Value)
{
    QFile fileDevice(m_filename); // 定义QFile对象，设置文件名
    if(!fileDevice.open(QIODevice::WriteOnly)) // 以只写模式打开
        return;

    QDataStream fileStream(&fileDevice); // 创建QDataStream对象
    fileStream.setVersion(QDataStream::Qt_6_2); // 设置版本号，写入和读取时使用的版本要兼容
    if(ui->radio_BigEndian->isChecked()) // 设置字节序
        fileStream.setByteOrder(QDataStream::BigEndian);
    else
        fileStream.setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置float和double的精度
        fileStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    fileStream << Value; // 用流写入操作符写入
    fileDevice.close();
}

void MainWindow::on_btnInt16_Write_clicked()
{
    //qint16类型数据，写入
    qint16 Value = ui->spin_Int16->value();
    writeByStream(Value);
}


void MainWindow::on_btnInt8_Write_clicked()
{
    qint8 Value = ui->spin_Int8->value();
    writeByStream(Value);
}


void MainWindow::on_btnUInt8_Write_clicked()
{
    quint8 Value = ui->spin_UInt8->value();
    writeByStream(Value);
}


void MainWindow::on_btnInt32_Write_clicked()
{
    qint32 Value = ui->spin_Int32->value();
    writeByStream(Value);
}


void MainWindow::on_btnUInt16_Write_clicked()
{
    quint16 Value = ui->spin_UInt16->value();
    writeByStream(Value);
}


void MainWindow::on_btnInt64_Write_clicked()
{
    qint64 Value = ui->spin_Int64->value();
    writeByStream(Value);
}


void MainWindow::on_btnBool_Write_clicked()
{
    // bool 类型数据，写入
    bool value = ui->chkBox_In->isChecked();
    writeByStream(value);
}


void MainWindow::on_btnFloat16_Write_clicked()
{
    qfloat16 Value = ui->spin_Float16->value();
    writeByStream(Value);
}


void MainWindow::on_btnFloat_Write_clicked()
{
    float Value = ui->spin_Float->value();
    writeByStream(Value);
}


void MainWindow::on_btnDouble_Write_clicked()
{
    double Value = ui->spin_Double->value();
    writeByStream(Value);
}


void MainWindow::on_btnStr_Write_clicked()
{
    // char* 字符串
    QString str = ui->editStr_In->text();
    char* Value = str.toLocal8Bit().data();
    writeByStream(Value);
}


void MainWindow::on_btnQStr_Write_clicked()
{
    // QString 字符串，写入
    QString Value = ui->editQStr_In->text();
    writeByStream(Value);
}


void MainWindow::on_btnFont_Write_clicked()
{
    // QFont类型数据，写入
    QFont font = ui->btnFont_In->font();
    writeByStream(font);
}


void MainWindow::on_btnColor_Write_clicked()
{
    // QColor类型数据，写入
    QPalette plet = ui->btnColor_In->palette();
    QColor color = plet.buttonText().color();
    writeByStream(color); // 向文件写入QColor类型数据
}


void MainWindow::on_btnColor_In_clicked()
{
    // 选择颜色
    QPalette plet = ui->btnColor_In->palette();
    QColor color = plet.buttonText().color();
    color = QColorDialog::getColor(color);
    if(color.isValid())
    {
        plet.setColor(QPalette::ButtonText, color);
        ui->btnColor_In->setPalette(plet);
    }
}


void MainWindow::on_btnFont_In_clicked()
{
    // 选择字体
    QFont font = ui->btnFont_In->font();
    bool OK = false;
    font = QFontDialog::getFont(&OK, font, this);
    if(OK)
        ui->btnFont_In->setFont(font);
}


template<class T>
void MainWindow::readByStream(T &Value)
{
    if(!QFile::exists(m_filename))
    {
        QMessageBox::critical(this, "错误", "文件不存在，文件名：\n" + m_filename);
    }
    QFile fileDevice(m_filename);
    if(!fileDevice.open(QIODevice::ReadOnly))
        return;

    QDataStream fileStream(&fileDevice); // 创建QDataStream对象
    fileStream.setVersion(QDataStream::Qt_6_2); // 设置版本号
    if(ui->radio_BigEndian->isChecked()) // 设置字节序
        fileStream.setByteOrder(QDataStream::BigEndian);
    else
        fileStream.setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置浮点数精度
        fileStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    fileStream >> Value; // 使用流读取操作符读出数据
    fileDevice.close();
}

void MainWindow::on_btnInt8_Read_clicked()
{
    qint8 value = 0;
    readByStream(value);
    ui->edit_Int8->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUInt8_Read_clicked()
{
    quint8 value = 0;
    readByStream(value);
    ui->edit_UInt8->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt16_Read_clicked()
{
    qint16 value = 0;
    readByStream(value);
    ui->edit_Int16->setText(QString("%1").arg(value));
}


void MainWindow::on_btnUIn16_Read_clicked()
{
    quint16 value = 0;
    readByStream(value);
    ui->edit_UInt16->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt32_Read_clicked()
{
    qint32 value = 0;
    readByStream(value);
    ui->edit_Int32->setText(QString("%1").arg(value));
}


void MainWindow::on_btnInt64_Read_clicked()
{
    qint64 value = 0;
    readByStream(value);
    ui->edit_Int64->setText(QString("%1").arg(value));
}


void MainWindow::on_btnBool_Read_clicked()
{
    // bool 类型数据，读出
    bool value = false;
    readByStream(value);
    ui->chkBox_Out->setChecked(value);
}


void MainWindow::on_btnInt_Read_clicked()
{
    qfloat16 value = 0;
    readByStream(value);
    float val = value; // 转换为float类型，因为QString::asprintf()不支持qfloat16类型
    ui->edit_Float16->setText(QString::asprintf("%.2f", val));
}


void MainWindow::on_btnFloat_Read_clicked()
{
    float value = 0;
    readByStream(value);
    ui->edit_Float->setText(QString::asprintf("%.4f", value));
}


void MainWindow::on_btnDouble_Read_clicked()
{
    double value = 0;
    readByStream(value);
    ui->edit_Double->setText(QString::asprintf("%.4f", value));
}


void MainWindow::on_btnStr_Read_clicked()
{
    // char* 字符串，读出
    char* value;
    readByStream(value);
    QString str(value); // 转换为QString类型才能在界面上显示
    ui->editStr_Out->setText(str);
}


void MainWindow::on_btnQStr_Read_clicked()
{
    // QString 字符串，读出
    QString value = "";
    readByStream(value);
    ui->editQStr_Out->setText(value);
}


void MainWindow::on_btnFont_Read_clicked()
{
    //QFont类型数据，读出
    QFont font;
    readByStream(font);
    ui->editFont_Out->setFont(font); // 设置编辑框的文字字体
}


void MainWindow::on_btnColor_Read_clicked()
{
    // QColor类型数据，读出
    QColor color = Qt::black;
    readByStream(color);
    QPalette plet = ui->editColor_Out->palette();
    plet.setColor(QPalette::Text, color);
    ui->editColor_Out->setPalette(plet); // 设置为编辑框的文字颜色
}


void MainWindow::on_actSaveALL_triggered()
{
    // 连续写入文件
    QFile fileDevice(m_filename);
    if(!fileDevice.open(QIODevice::WriteOnly))
        return;
    QDataStream fileStream(&fileDevice);
    fileStream.setVersion(QDataStream::Qt_6_2); // 设置版本号
    if(ui->radio_BigEndian->isChecked()) // 设置字节序
        fileStream.setByteOrder(QDataStream::BigEndian);
    else
        fileStream.setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置浮点精度
        fileStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    // 按顺序写入各种数据
    qint8 int8_Value = ui->spin_Int8->value();
    fileStream<<int8_Value;

    quint8 uint8_Value = ui->spin_UInt8->value();
    fileStream << uint8_Value;

    qint16 int16_Value = ui->spin_Int16->value();
    fileStream << int16_Value;

    quint16 uint16_Value = ui->spin_UInt16->value();
    fileStream << uint16_Value;

    qint32 int32_Value = ui->spin_Int32->value();
    fileStream << int32_Value;

    qint64 int64_Value = ui->spin_Int64->value();
    fileStream << int64_Value;

    bool bool_value = ui->chkBox_In->isChecked();
    fileStream << bool_value;

    qfloat16 float16_value = ui->spin_Float16->value();
    fileStream << float16_value;

    float float_value = ui->spin_Float->value();
    fileStream << float_value;

    double double_value = ui->spin_Double->value();
    fileStream << double_value;

    QString str = ui->editStr_In->text();
    char* charStr = str.toLocal8Bit().data();
    fileStream << charStr;

    QString str_value = ui->editQStr_In->text();
    fileStream << str_value;

    QFont font = ui->btnFont_In->font();
    fileStream << font;

    QPalette plet = ui->btnColor_In->palette();
    QColor color = plet.buttonText().color();
    fileStream << color;

    fileDevice.close();
    QMessageBox::information(this, "消息", "数据连续写入文件完成.");
}


void MainWindow::on_actReadALL_triggered()
{
    // 连续从文件读取
    if(!QFile::exists(m_filename))
    {
        QMessageBox::critical(this, "错误", "文件不存在，文件名：" + m_filename);
        return;
    }
    QFile fileDevice(m_filename);
    if(!fileDevice.open(QIODevice::ReadOnly))
        return;
    QDataStream fileStream(&fileDevice);
    fileStream.setVersion(QDataStream::Qt_6_2); // 设置版本号
    if(ui->radio_BigEndian->isChecked()) // 设置字节序
        fileStream.setByteOrder(QDataStream::BigEndian);
    else
        fileStream.setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置浮点精度
        fileStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream.setFloatingPointPrecision(QDataStream::DoublePrecision);

    fileStream.startTransaction(); // 开始读取操作事务
    qint8 int8_Value = 0;
    fileStream>>int8_Value;
    ui->edit_Int8->setText(QString("%1").arg(int8_Value));

    quint8 uint8_Value = 0;
    fileStream >> uint8_Value;
    ui->edit_UInt8->setText(QString("%1").arg(uint8_Value));

    qint16 int16_Value = 0;
    fileStream >> int16_Value;
    ui->edit_Int16->setText(QString("%1").arg(int16_Value));

    quint16 uint16_Value = 0;
    fileStream >> uint16_Value;
    ui->edit_UInt16->setText(QString("%1").arg(uint16_Value));

    qint32 int32_Value = 0;
    fileStream >> int32_Value;
    ui->edit_Int32->setText(QString("%1").arg(int32_Value));

    qint64 int64_Value = 0;
    fileStream >> int64_Value;
    ui->edit_Int64->setText(QString("%1").arg(int64_Value));

    bool bool_value;
    fileStream >> bool_value;
    ui->chkBox_Out->setChecked(bool_value);

    qfloat16 float16_value = 0;
    fileStream >> float16_value;
    float val = float16_value;
    ui->edit_Float16->setText(QString::asprintf("%.4f", val));

    float float_value = 0;
    fileStream >> float_value;
    ui->edit_Float->setText(QString::asprintf("%.4f", float_value));

    double double_value = 0;
    fileStream >> double_value;
    ui->edit_Double->setText(QString::asprintf("%.4f", double_value));

    char* charStr;
    fileStream >> charStr; // char* 字符串
    QString str(charStr); // 转换为QString字符串
    ui->editStr_Out->setText(str);

    QString str_value = "";
    fileStream >> str_value;
    ui->editQStr_Out->setText(str_value);

    QFont font;
    fileStream >> font;
    ui->editFont_Out->setFont(font);

    QColor color;
    fileStream >> color;
    QPalette plet = ui->editColor_Out->palette();
    plet.setColor(QPalette::Text, color);
    ui->editColor_Out->setPalette(plet);

    if(fileStream.commitTransaction())
        QMessageBox::information(this, "消息", "从文件连续读取数据完成.");
    else
        QMessageBox::critical(this, "错误", "文件读取过程出错，请检查文件格式");

    fileDevice.close();
}

