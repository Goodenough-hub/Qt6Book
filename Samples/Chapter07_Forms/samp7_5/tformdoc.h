#ifndef TFORMDOC_H
#define TFORMDOC_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QFontDialog>
#include <QTextStream>

namespace Ui {
class TFormDoc;
}

class TFormDoc : public QWidget
{
    Q_OBJECT
private:
    QString m_filename; // 当前文件
    bool m_fileOpened = false; // 文件已打开
public:
    explicit TFormDoc(QWidget *parent = nullptr);
    ~TFormDoc();
    void loadFromFile(QString& aFileName); // 打开一个文件
    void saveToFile(); // 保存文件
    QString currentFileName(); // 返回当前文件名
    bool isFileOpened(); // 是否打开了文件
    void setEditFont(); // 设置字体
    void textCut(); // 剪切
    void textCopy(); // 复制
    void textPaste(); // 粘贴
private:
    Ui::TFormDoc *ui;
};

#endif // TFORMDOC_H
