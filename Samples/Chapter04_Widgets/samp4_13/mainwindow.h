#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDate>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // 单元格的类型，在创建单元格时用于设置type
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartM,ctScore};

    //各字段在表格中的列号
    enum FieldColNum{colName=0, colSex,colBirth,colNation,colScore,colPartyM};

    QLabel *labCellIndex;
    QLabel *labCellType;
    QLabel *labStudID;

    int m_rows = 0; // 初始化表格时需要确定表格的行数

    // 为某一行创建items
    void createItemARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnIniData_clicked();

    void on_btnSetRows_clicked();

    void on_tableinfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAddRow_clicked();

    void on_btnDelCurRow_clicked();

    void on_btnResizeRows_clicked();

    void on_btnResizeColumns_clicked();

    void on_chkBoxTabEditable_clicked(bool checked);

    void on_chkBoxHeaderH_clicked(bool checked);

    void on_chkBoxHeaderV_clicked(bool checked);

    void on_chkBoxRowColor_clicked(bool checked);

    void on_rBtnSelectRow_clicked();

    void on_rBtnSelectItem_clicked();

    void on_btnReadToEdit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
