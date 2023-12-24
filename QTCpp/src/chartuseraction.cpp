
#include "chartuseraction.h"

CChartUserAction::CChartUserAction(QCustomPlot *custom_plot):
    ActionHandler(new CActionHandler(custom_plot))
{
    QObject::connect(custom_plot,SIGNAL(mouseDoubleClick(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseMove(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mousePress(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseRelease(QMouseEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));
    QObject::connect(custom_plot,SIGNAL(mouseWheel(QWheelEvent*)),ActionHandler,SLOT(SetPlotEvent(QMouseEvent*)));

    QObject::connect(custom_plot,SIGNAL(afterReplot()),ActionHandler,SLOT(UpdateView()));
}

void CChartUserAction::SetMode(EToolType mode)
{
    ActionHandler->SetActiveTool(mode);
}

