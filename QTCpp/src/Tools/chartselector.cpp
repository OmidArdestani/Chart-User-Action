
#include "chartselector.h"

CChartSelector::CChartSelector(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{

}


EToolType CChartSelector::GetType()
{
    return EToolType::Selector;
}

void CChartSelector::UpdateWithMouseEvent(QMouseEvent *event)
{
}

void CChartSelector::SetVisibility(bool value)
{
}

void CChartSelector::SetColor(QColor color)
{
}

void CChartSelector::SetWorkingGraphIndex(int index)
{
}

void CChartSelector::SetGeometry(int x, int y, int width, int height)
{
}

void CChartSelector::UpdateView()
{
}
