#include "mainwindow.h"
#include "./ui_mainwindow.h"

bool MainWindow::initWrite()
{
    // 初始化写文件操作，创建QFile和QDataStream对象
    fileDevice = new QFile(m_filename);
    if(!fileDevice->open(QIODevice::WriteOnly)) // 打开或创建文件
        return false;
    fileStream = new QDataStream(fileDevice);
    fileStream->setVersion(QDataStream::Qt_6_2);
    if(ui->radio_BigEndian->isChecked())
        fileStream->setByteOrder(QDataStream::BigEndian);
    else
        fileStream->setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置浮点数精度
        fileStream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream->setFloatingPointPrecision(QDataStream::DoublePrecision);
    return true;
}

bool MainWindow::iniRead()
{
    // 初始化读文件操作，创建QFile和QDataStream对象
    if(!QFile::exists(m_filename))
    {
        QMessageBox::critical(this, "错误", "文件不存在，文件名："+m_filename);
        return false;
    }
    fileDevice = new QFile(m_filename);
    if(!fileDevice->open(QIODevice::ReadOnly)) // 打开或创建文件
        return false;
    fileStream = new QDataStream(fileDevice);
    fileStream->setVersion(QDataStream::Qt_6_2);
    if(ui->radio_BigEndian->isChecked())
        fileStream->setByteOrder(QDataStream::BigEndian);
    else
        fileStream->setByteOrder(QDataStream::LittleEndian);

    if(ui->radio_Single->isChecked()) // 设置浮点数精度
        fileStream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    else
        fileStream->setFloatingPointPrecision(QDataStream::DoublePrecision);
    return true;
}

void MainWindow::delFileStream()
{
    fileDevice->close(); // 关闭文件
    delete fileStream;
    delete fileDevice;
}

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
    m_filename = QFileDialog::getOpenFileName(this, "选择一个文件", curPath, "raw文件(*.raw)");

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
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qint16 Value = ui->spin_Int16->value();
        fileStream->writeRawData((char*)&Value, sizeof(qint16)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnInt8_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qint8 Value = ui->spin_Int8->value();
        fileStream->writeRawData((char*)&Value, sizeof(qint8)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnUInt8_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        quint8 Value = ui->spin_UInt8->value();
        fileStream->writeRawData((char*)&Value, sizeof(quint8)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnInt32_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qint32 Value = ui->spin_Int32->value();
        fileStream->writeRawData((char*)&Value, sizeof(qint32)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnUInt16_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        quint16 Value = ui->spin_UInt16->value();
        fileStream->writeRawData((char*)&Value, sizeof(quint16)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnInt64_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qint64 Value = ui->spin_Int64->value();
        fileStream->writeRawData((char*)&Value, sizeof(qint64)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnBool_Write_clicked()
{
    // bool 类型数据，写入
    bool value = ui->chkBox_In->isChecked();
    writeByStream(value);
}


void MainWindow::on_btnFloat16_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qfloat16 Value = ui->spin_Float16->value();
        fileStream->writeRawData((char*)&Value, sizeof(qfloat16)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnFloat_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        qint32 Value = ui->spin_Float->value();
        fileStream->writeRawData((char*)&Value, sizeof(qint32)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnDouble_Write_clicked()
{
    if(initWrite()) // 初始化写文件操作，创建QFile和QDataStream对象
    {
        double Value = ui->spin_Double->value();
        fileStream->writeRawData((char*)&Value, sizeof(double)); // 写qint32类型数据
        delFileStream(); // 关闭文件，删除QFile和QDataStream对象
    }
}


void MainWindow::on_btnStr_Write_clicked()
{
    // 写入字符串，UTF-8编码
    if(initWrite())
    {
        QString str = ui->editStr_In->text();
        QByteArray btArray = str.toUtf8(); // UTF-8编码
        fileStream->writeBytes(btArray, btArray.length());
        delFileStream();
    }
}


void MainWindow::on_btnQStr_Write_clicked()
{
    // 写入字符串，Latin1编码
    if(initWrite())
    {
        QString str = ui->editQStr_In->text();
        QByteArray btArray = str.toLatin1(); // Latin1编码
        fileStream->writeBytes(btArray, btArray.length());
        delFileStream();
    }
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
    if(iniRead())
    {
        qint8 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(qint8));
        ui->edit_Int8->setText(QString("%1").arg(Value));
        delFileStream();
    }
}


void MainWindow::on_btnUInt8_Read_clicked()
{
    if(iniRead())
    {
        quint8 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(quint8));
        ui->edit_UInt8->setText(QString("%1").arg(Value));
        delFileStream();
    }
}


void MainWindow::on_btnInt16_Read_clicked()
{
    if(iniRead())
    {
        qint16 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(qint16));
        ui->edit_Int16->setText(QString("%1").arg(Value));
        delFileStream();
    }
}


void MainWindow::on_btnUIn16_Read_clicked()
{
    if(iniRead())
    {
        quint16 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(quint16));
        ui->edit_UInt16->setText(QString("%1").arg(Value));
        delFileStream();
    }
}


void MainWindow::on_btnInt32_Read_clicked()
{
    if(iniRead())
    {
        qint32 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(qint32));
        ui->edit_Int32->setText(QString("%1").arg(Value));
        delFileStream();
    }
}


void MainWindow::on_btnInt64_Read_clicked()
{
    if(iniRead())
    {
        qint64 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(qint64));
        ui->edit_Int64->setText(QString("%1").arg(Value));
        delFileStream();
    }
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
    if(iniRead())
    {
        qfloat16 Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(qfloat16));
        float val = Value;
        ui->edit_Float16->setText(QString::asprintf("%.4f", val));
        delFileStream();
    }
}


void MainWindow::on_btnFloat_Read_clicked()
{
    if(iniRead())
    {
        float Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(float));
        ui->edit_Float->setText(QString::asprintf("%.4f", Value));
        delFileStream();
    }
}


void MainWindow::on_btnDouble_Read_clicked()
{
    if(iniRead())
    {
        double Value = 0;
        fileStream->readRawData((char*)&Value, sizeof(double));
        ui->edit_Double->setText(QString::asprintf("%.4f", Value));
        delFileStream();
    }
}


void MainWindow::on_btnStr_Read_clicked()
{
    // 读取字符串，UTF-8编码
    if(iniRead())
    {
        char *buf;
        uint strLen;
        fileStream->readBytes(buf, strLen); // 同时读取字符串长度和字符串内容
        QString str = QString::fromUtf8(buf, strLen); // 用UTF-8编码解码数据
        ui->editStr_Out->setText(str);
        delFileStream();
        delete buf; // 手动删除缓存区
        QString info = QString("读取数据缓冲区长度 = %1（字节）").arg(strLen);
        QMessageBox::information(this, "信号提示", info);
    }
}


void MainWindow::on_btnQStr_Read_clicked()
{
    // 读取字符串，Latin1编码
    if(iniRead())
    {
        char *buf;
        uint strLen;
        fileStream->readBytes(buf, strLen); // 同时读取字符串长度和字符串内容
        QString str = QString::fromLatin1(buf, strLen); // 用Latin1编码解码数据
        ui->editQStr_Out->setText(str);
        delFileStream();
        delete buf; // 手动删除缓存区
        QString info = QString("读取数据缓冲区长度 = %1（字节）").arg(strLen);
        QMessageBox::information(this, "信号提示", info);
    }
}


void MainWindow::on_actSaveALL_triggered()
{
    // 连续写入文件
    if(!initWrite())
        return;

    // 按顺序写入各种数据
    qint8 int8_Value = ui->spin_Int8->value();
    fileStream->writeRawData((char*)&int8_Value, sizeof(qint8));

    quint8 uint8_Value = ui->spin_UInt8->value();
    fileStream->writeRawData((char*)&uint8_Value, sizeof(quint8));

    qint16 int16_Value = ui->spin_Int16->value();
    fileStream->writeRawData((char*)&int16_Value, sizeof(qint16));

    quint16 uint16_Value = ui->spin_UInt16->value();
    fileStream->writeRawData((char*)&uint16_Value, sizeof(quint16));

    qint32 int32_Value = ui->spin_Int32->value();
    fileStream->writeRawData((char*)&int32_Value, sizeof(qint32));

    qint64 int64_Value = ui->spin_Int64->value();
    fileStream->writeRawData((char*)&int64_Value, sizeof(qint64));

    bool bool_value = ui->chkBox_In->isChecked();
    fileStream->writeRawData((char*)&bool_value, sizeof(bool));

    qfloat16 float16_value = ui->spin_Float16->value();
    fileStream->writeRawData((char*)&float16_value, sizeof(qfloat16));

    float float_value = ui->spin_Float->value();
    fileStream->writeRawData((char*)&float_value, sizeof(float));

    double double_value = ui->spin_Double->value();
    fileStream->writeRawData((char*)&double_value, sizeof(double));

    QString str = ui->editStr_In->text();
    QByteArray btArray = str.toUtf8(); // UTF-8
    fileStream->writeBytes(btArray, btArray.length());

    str = ui->editQStr_In->text();
    btArray = str.toLatin1(); // UTF-8
    fileStream->writeBytes(btArray, btArray.length());

    // 数据写入完成
    delFileStream();
    QMessageBox::information(this, "消息", "数据连续写入文件完成.");
}


void MainWindow::on_actReadALL_triggered()
{
    // 连续从文件读取
    if(!iniRead())
        return;

    qint8 int8_Value = 0;
    fileStream->readRawData((char*)&int8_Value, sizeof(qint8));
    ui->edit_Int8->setText(QString("%1").arg(int8_Value));

    quint8 uint8_Value = 0;
    fileStream->readRawData((char*)&uint8_Value, sizeof(quint8));
    ui->edit_UInt8->setText(QString("%1").arg(uint8_Value));

    qint16 int16_Value = 0;
    fileStream->readRawData((char*)&int16_Value, sizeof(qint16));
    ui->edit_Int16->setText(QString("%1").arg(int16_Value));

    quint16 uint16_Value = 0;
    fileStream->readRawData((char*)&uint16_Value, sizeof(quint16));
    ui->edit_UInt16->setText(QString("%1").arg(uint16_Value));

    qint32 int32_Value = 0;
    fileStream->readRawData((char*)&int32_Value, sizeof(qint32));
    ui->edit_Int32->setText(QString("%1").arg(int32_Value));

    qint64 int64_Value = 0;
    fileStream->readRawData((char*)&int64_Value, sizeof(qint64));
    ui->edit_Int64->setText(QString("%1").arg(int64_Value));

    bool bool_value;
    fileStream->readRawData((char*)&bool_value, sizeof(bool));
    ui->chkBox_Out->setChecked(bool_value);

    qfloat16 float16_value = 0;
    fileStream->readRawData((char*)&float16_value, sizeof(qfloat16));
    float val = float16_value;
    ui->edit_Float16->setText(QString::asprintf("%.4f", val));

    float float_value = 0;
    fileStream->readRawData((char*)&float_value, sizeof(float));
    ui->edit_Float->setText(QString::asprintf("%.4f", float_value));

    double double_value = 0;
    fileStream->readRawData((char*)&double_value, sizeof(double));
    ui->edit_Double->setText(QString::asprintf("%.4f", double_value));

    char *buf;
    uint strLen;
    fileStream->readBytes(buf, strLen); // 读取字符串
    QString str_value = QString::fromUtf8(buf, strLen); // 用UTF-8编码
    ui->editStr_Out->setText(str_value);

    fileStream->readBytes(buf, strLen); // 读取下一个字符串
    str_value = QString::fromLatin1(buf, strLen); // 用Latin1编码
    ui->editQStr_Out->setText(str_value);

    // 读取完成
    delFileStream();
    QMessageBox::information(this, "消息", "从文件连续读取数据完成.");
}

