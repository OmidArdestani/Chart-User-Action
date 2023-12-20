
#include "cchartmeasure.h"

CChartMeasure::CChartMeasure(QObject *parent)
    : QObject{parent}
{

}


ToolType CChartMeasure::GetType()
{
    return ToolType::Measure;
}

void CChartMeasure::Update(QMouseEvent *event)
{

}

void CChartMeasure::ShowSetting()
{

}

void CChartMeasure::SetVisibility()
{

}
