#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

#include <chartuseraction.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // insert graph
    ui->wPlot->addGraph(ui->wPlot->xAxis,ui->wPlot->yAxis);
    GenerateSinData();

    CChartUserAction* chart_action = new CChartUserAction(ui->wPlot);
    chart_action->SetMode(EToolType::Selector);
    chart_action->show();


    QTimer *tr=new QTimer(this);

    connect(tr,SIGNAL(timeout()),ui->wPlot,SLOT(replot()));
    tr->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GenerateSinData()
{
    QCustomPlot* plot = ui->wPlot;

    double freq = 10; //hz
    double number_of_points = 100;
    double step = M_2_PI / number_of_points;

    QVector<double> x_data(number_of_points),y_data(number_of_points);

    int index = 0;
    for(double t = 0 ; t < M_2_PI ; t += step)
    {
        x_data[index] = t;
        y_data[index++] = std::sin(2 * M_PI * freq * t);
    }

    plot->graph(0)->setData(x_data,y_data);
    plot->rescaleAxes();
}
