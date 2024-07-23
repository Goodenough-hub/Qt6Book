#include "tdialogdata.h"
#include "ui_tdialogdata.h"

TDialogData::TDialogData(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogData)
{
    ui->setupUi(this);
}

TDialogData::~TDialogData()
{
    delete ui;
}

void TDialogData::setUpdateRecord(QSqlRecord &recData)
{
    // 编辑记录，将更新记录数据到界面
    m_record = recData; // 记录存入私有变量
    ui->spinEmpNo->setEnabled(false); // 工号不允许编辑
    setWindowTitle("更新记录");
    // 根据recData的数据更新界面显示内容
    ui->spinEmpNo->setValue(recData.value("empNo").toInt());
    ui->editName->setText(recData.value("Name").toString());
    ui->comboSex->setCurrentText(recData.value("Gender").toString());
    ui->editBirth->setDate(recData.value("Birthday").toDate());
    ui->comboProvince->setCurrentText(recData.value("Department").toString());
    ui->spinSalary->setValue(recData.value("Memo").toInt());
    ui->editMemo->setPlainText(recData.value("Memo").toString());

    QVariant va = recData.value("Photo");
    if(!va.isValid())
        ui->LabPhoto->clear();
    else
    {
        QByteArray data = va.toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->LabPhoto->setPixmap(pic.scaledToWidth(ui->LabPhoto->size().width()));
    }
}

void TDialogData::setInsertRecord(QSqlRecord &recData)
{
    // 插入记录，无须更新界面显示内容，但是要存储recData的字段结构
    m_record = recData; // recData保存到私有变量中
    ui->spinEmpNo->setEnabled(true); // 插入的记录，允许编辑工号
    setWindowTitle("插入新纪录");
    ui->spinEmpNo->setValue(recData.value("empNo").toInt());
}

QSqlRecord TDialogData::getRecordData()
{
    // 点击 确定 按钮，界面数据保存到变量m_record中
    m_record.setValue("empNo", ui->spinEmpNo->value());
    m_record.setValue("Name", ui->editName->text());
    m_record.setValue("Gender", ui->comboSex->currentText());
    m_record.setValue("Birthday", ui->editBirth->date());
    m_record.setValue("Province", ui->comboProvince->currentText());
    m_record.setValue("Department", ui->comboDep->currentText());
    m_record.setValue("Salary", ui->spinSalary->value());
    m_record.setValue("Memo", ui->editMemo->toPlainText());
    // 编辑照片时已经修改了m_record的Photo字段的值
    return m_record; // 以记录作为返回值
}

void TDialogData::on_btnClearPhoto_clicked()
{
    // 清除照片
    ui->LabPhoto->clear();
    m_record.setNull("Photo"); // Photo字段清空
}


void TDialogData::on_btnSetPhoto_clicked()
{
    // 导入照片
    QString aFile = QFileDialog::getOpenFileName(this, "选择图片文件", "", "照片(*.jpg)");
    if(aFile.isEmpty())
        return;
    QByteArray data;
    QFile *file = new QFile(aFile);
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();
    delete file;

    m_record.setValue("Photo", data); // 图片保存到Photo字段中
    QPixmap pic;
    pic.loadFromData(data);
    ui->LabPhoto->setPixmap(pic.scaledToWidth(ui->LabPhoto->size().width()));
}

