
#include "chartmeasure.h"

CChartMeasure::CChartMeasure(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{

}

EToolType CChartMeasure::GetType()
{
    return EToolType::Measure;
}

void CChartMeasure::UpdateWithMouseEvent(QMouseEvent *event)
{
}

void CChartMeasure::SetVisibility(bool value)
{
}

void CChartMeasure::SetColor(QColor color)
{
}

void CChartMeasure::SetWorkingGraphIndex(int index)
{
}

void CChartMeasure::SetGeometry(int x, int y, int width, int height)
{
}

void CChartMeasure::UpdateView()
{
}
