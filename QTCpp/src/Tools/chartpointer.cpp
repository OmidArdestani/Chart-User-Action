
#include "chartpointer.h"

CChartPointer::CChartPointer(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{

}


EToolType CChartPointer::GetType()
{
    return EToolType::Pointer;
}


void CChartPointer::UpdateWithMouseEvent(QMouseEvent *event)
{
}

void CChartPointer::SetVisibility(bool value)
{
}

void CChartPointer::SetColor(QColor color)
{
}

void CChartPointer::SetWorkingGraphIndex(int index)
{
}

void CChartPointer::SetGeometry(int x, int y, int width, int height)
{
}

void CChartPointer::UpdateView()
{
}
