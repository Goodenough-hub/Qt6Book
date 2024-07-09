#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTreeWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum treeColNum{colItem=0,colItemTye,colDate};
    enum treeItemType{itTopItem=1001, itGroupItem, itImageItem};
    void changeItemCaption(QTreeWidgetItem *item); // 遍历item

    QLabel *labFileName;
    QLabel *labNodeText;
    QSpinBox *spinRatio;
    QPixmap m_pixmap;
    float m_ratio;

    void displayImage(QTreeWidgetItem *item);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_actDeleteItem_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actSacnItems_triggered();

    void on_actZoomFitW_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomRealSize_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actDockVisible_triggered(bool checked);

    void on_actDockerFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
