
#include "chartshape.h"

CChartShape::CChartShape(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{

}

EToolType CChartShape::GetType()
{
    return EToolType::Shape;
}

void CChartShape::UpdateWithMouseEvent(QMouseEvent *event)
{
}

void CChartShape::SetVisibility(bool value)
{
}

void CChartShape::SetColor(QColor color)
{
}

void CChartShape::SetWorkingGraphIndex(int index)
{
}

void CChartShape::SetGeometry(int x, int y, int width, int height)
{
}

void CChartShape::UpdateView()
{
}
