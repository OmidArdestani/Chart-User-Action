
#include "chartuseraction.h"

CChartUserAction::CChartUserAction(QObject *parent)
    : QObject{parent},ActionHandler{new CActionHandler()}
{

}

CChartUserAction::CChartUserAction(QCustomPlot *custom_plot)
{
    connect(custom_plot,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(OnMouseDoubleClick(QMouseEvent*)));
    connect(custom_plot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(OnMouseMove(QMouseEvent*)));
    connect(custom_plot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(OnMousePress(QMouseEvent*)));
    connect(custom_plot,SIGNAL(mouseRlease(QMouseEvent*)),this,SLOT(OnMouseRelease(QMouseEvent*)));
    connect(custom_plot,SIGNAL(mouseWheel(QMouseEvent*)),this,SLOT(OnMouseWheel(QMouseEvent*)));

}

