#include "mainwindow.h"
#include "ui_mainwindow.h"

#include    <QtCharts>

void MainWindow::createChart()
{
    QChartView *chartView=new QChartView(this); //图表视图
    QChart *chart = new QChart();       //图表,类似于图形项
    chart->setTitle("简单函数曲线");

    chartView->setChart(chart);     //chart添加到chartView
    this->setCentralWidget(chartView);

    //创建曲线序列
    QLineSeries *series0 = new QLineSeries();   //折线序列
    QLineSeries *series1 = new QLineSeries();
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
    chart->addSeries(series0);  //序列添加到图表
    chart->addSeries(series1);


    //序列添加数值
    qreal   t=0,y1,y2,intv=0.1;
    int cnt=100;
    for(int i=0;i<cnt;i++)
    {
        y1=qSin(t);
        series0->append(t,y1);

        y2=qSin(t+20);
        series1->append(t,y2);

        t+=intv;
    }


    //创建坐标轴
    QValueAxis *axisX = new QValueAxis; //X 轴
    axisX->setRange(0, 10);             //设置坐标轴范围
    axisX->setTitleText("时间(秒)");     //标题

    QValueAxis *axisY = new QValueAxis; //Y 轴
    axisY->setRange(-2, 2);
    axisY->setTitleText("数值");


    chart->addAxis(axisX, Qt::AlignBottom); //添加作为底边坐标轴
    chart->addAxis(axisY, Qt::AlignLeft);   //添加作为左边坐标轴

    series0->attachAxis(axisX); //为序列附加坐标轴
    series0->attachAxis(axisY);

    series1->attachAxis(axisX); //为序列附加坐标轴
    series1->attachAxis(axisY);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

