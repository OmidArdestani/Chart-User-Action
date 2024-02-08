
#include "chartuseraction.h"
#include <ui_chartuseraction.h>

CChartUserAction::CChartUserAction(QCustomPlot *custom_plot, QWidget *parent):
    QWidget(parent),
    ui(new Ui::CChartUserAction()),
    ActionHandler(new CActionHandler(custom_plot))
{
    ui->setupUi(this);

    InitPlotSlots(custom_plot);
    InitButtonsSlots();
}

void CChartUserAction::SetMode(EToolType mode)
{
    ActionHandler->SetActiveTool(mode);
}

void CChartUserAction::InitPlotSlots(QCustomPlot *custom_plot)
{
    QObject::connect(custom_plot,SIGNAL(mouseDoubleClick(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseMove(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mousePress(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseRelease(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseWheel(QWheelEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));

    QObject::connect(custom_plot,SIGNAL(afterReplot()),ActionHandler,SLOT(UpdateView()));
}

void CChartUserAction::InitButtonsSlots()
{
    connect(ui->pbArea,&QPushButton::clicked,[=](){ActionHandler->SetActiveTool(EToolType::Selector);});
    connect(ui->pbMarker,&QPushButton::clicked,[=](){ActionHandler->SetActiveTool(EToolType::Marker);});
    connect(ui->pbMeasure,&QPushButton::clicked,[=](){ActionHandler->SetActiveTool(EToolType::Measure);});
    connect(ui->pbPoint,&QPushButton::clicked,[=](){ActionHandler->SetActiveTool(EToolType::Pointer);});
    connect(ui->pbShape,&QPushButton::clicked,[=](){ActionHandler->SetActiveTool(EToolType::Shape);});
}

