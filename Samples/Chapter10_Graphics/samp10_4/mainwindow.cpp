#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::iniGraphicsSystem()
{
    // 创建图形/视图架构中的其他组件，包括场景和多个图形项
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect, this); // 为场景设置场景
    ui->graphicsView->setScene(scene); // 为视图设置场景
    // 画一个矩形框，其大小等于场景的大小
    QGraphicsRectItem *item = new QGraphicsRectItem(rect); // 矩形框的大小正好等于场景的大小
    // 可选择，可以获得焦点，但是不能移动
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    // 一个位于场景中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    // 矩形框内创建椭圆，图形项的局部坐标，左上角坐标为（-100， -50），宽200，高100
    item2->setPos(0, 0); // 图形项在场景中的坐标
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlag(QGraphicsItem::ItemIsMovable); // 能移动
    item2->setFlag(QGraphicsItem::ItemIsSelectable); // 可选择
    item2->setFlag(QGraphicsItem::ItemIsFocusable); // 可以获得焦点
    scene->addItem(item2);

    // 一个圆，中心位于场景的边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    // 矩形框内创建椭圆，图形项的局部坐标，左上角坐标为（-50，-50），宽100，高100
    item3->setPos(rect.right(), rect.bottom()); // 图形项在场景中的坐标
    item3->setBrush(QBrush(Qt::red));
    item3->setFlag(QGraphicsItem::ItemIsMovable); // 能移动
    item3->setFlag(QGraphicsItem::ItemIsSelectable); // 可选择
    item3->setFlag(QGraphicsItem::ItemIsFocusable); // 可以获得焦点
    scene->addItem(item3);
    scene->clearSelection();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord = new QLabel("View 坐标：", this);
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);
    labSceneCord = new QLabel("Scene 坐标：", this);
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);
    labItemCord = new QLabel("Item 坐标：", this);
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);
    // TGraphivsView组件view的设置
    ui->graphicsView->setCursor(Qt::CrossCursor); // 十字形光标
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag); // 开启鼠标追踪
    connect(ui->graphicsView, SIGNAL(mouseMovePoint(QPoint)), this, SLOT(do_mouseMovePoint(QPoint)));
    connect(ui->graphicsView, SIGNAL(mouseClicked(QPoint)), this, SLOT(do_mouseClicked(QPoint)));
    iniGraphicsSystem(); // 图形/视图架构初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QString str = QString::asprintf("Graphics View坐标，左上角总是（0， 0），宽度=%d，高度=%d", ui->graphicsView->width(), ui->graphicsView->height());
    ui->labViewSize->setText(str);

    QRectF rectF = ui->graphicsView->sceneRect(); // 场景的矩形区
    QString str2 = QString::asprintf("QGraphicsView::SceneRect=(Left,Top,Width,Height)=%.0f,%.0f,%.0f,%.0f", rectF.left(), rectF.top(), rectF.width(), rectF.height());
    ui->labViewRect->setText(str2);
    event->accept();
}

void MainWindow::do_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View 坐标：%d, %d", point.x(), point.y()));
    QPointF pointScene = ui->graphicsView->mapToScene(point); // 变换为场景坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标：%.0f, %.0f", pointScene.x(), pointScene.y()));
}

void MainWindow::do_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(point); // 变换为场景坐标
    QGraphicsItem *item = NULL;
    item = scene->itemAt(pointScene, ui->graphicsView->transform()); // 获取光标处的图形项
    if(item!=NULL)
    {
        QPointF pointItem = item->mapFromScene(pointScene); // 变换为图形项的局部坐标
        labItemCord->setText(QString::asprintf("Item 坐标：%.0f, %.0f", pointItem.x(), pointItem.y()));
    }
}
