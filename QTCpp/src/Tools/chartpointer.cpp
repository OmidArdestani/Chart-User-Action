#include "chartpointer.h"

#include <QString>

CChartPointer::CChartPointer(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{

    CaptionPointer = new QCPItemText(Plot);
    CaptionPointer->setPositionAlignment(Qt::AlignRight | Qt::AlignTop);
    CaptionPointer->position->setType(QCPItemPosition::ptAbsolute);
    CaptionPointer->setFont(QFont(Plot->font().family(), 10));
    CaptionPointer->setVisible(false);

    HorizontalLine = new QCPItemLine(plot);
    HorizontalLine->start->setType(QCPItemPosition::ptPlotCoords);
    HorizontalLine->end->setType(QCPItemPosition::ptPlotCoords);

    HorizontalLine->start->setCoords(plot->xAxis->range().lower,0.5);
    HorizontalLine->end->setCoords(plot->xAxis->range().upper,0.5);
    HorizontalLine->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));

    VerticalLine = new QCPItemLine(plot);
    VerticalLine->start->setType(QCPItemPosition::ptPlotCoords);
    VerticalLine->end->setType(QCPItemPosition::ptPlotCoords);

    VerticalLine->start->setCoords(0.5,plot->yAxis->range().lower);
    VerticalLine->end->setCoords(0.5,plot->yAxis->range().upper);
    VerticalLine->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));



    SetColor(QColor(99, 102, 123));

    SetWorkingGraphIndex(graph_index);

    plot->replot();
}


EToolType CChartPointer::GetType()
{
    return EToolType::Pointer;
}


void CChartPointer::UpdateWithMouseEvent(QMouseEvent *event)
{

    captionPosition = QPointF(event->x(),event->y());
    CaptionPointer->position->setCoords(captionPosition);

    if(event->type() == QEvent::MouseMove)
    {
        auto h_updated_value = Plot->yAxis->pixelToCoord(event->y());
        HorizontalLine->start->setCoords(Plot->xAxis->range().lower,h_updated_value);
        HorizontalLine->end->setCoords(Plot->xAxis->range().upper,h_updated_value);

        auto v_updated_value = Plot->xAxis->pixelToCoord(event->x());
        VerticalLine->start->setCoords(v_updated_value,Plot->yAxis->range().lower);
        VerticalLine->end->setCoords(v_updated_value,Plot->yAxis->range().upper);
        CurrentKey = Plot->xAxis->pixelToCoord(event->x());
        CurrentValue = Plot->yAxis->pixelToCoord(event->y());
    }
}

void CChartPointer::SetVisibility(bool value)
{
}

void CChartPointer::SetColor(QColor color)
{
    this->Color = color;
    QPen pen;

    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    pen.setColor(color);

    HorizontalLine->setPen(pen);
    VerticalLine->setPen(pen);


}

void CChartPointer::SetWorkingGraphIndex(int index)
{
}

void CChartPointer::SetGeometry(int x, int y, int width, int height)
{
}


CChartPointerBuilder::CChartPointerBuilder(QCustomPlot *plot):IPlotToolBuilder(plot)
{

}

void CChartPointerBuilder::UpdateWithMouseEvent(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CChartPointer(Plot);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        this->CurrentTool->SetVisibility(true);
        break;
    }
}

QCPItemText *CChartPointer::GetCaptionPointer()
{
    return CaptionPointer;

}

void CChartPointerBuilder::UpdateView()
{
    if(!CurrentTool)return;

    this->CurrentTool->UpdateView();
}

double CChartPointer::GetValue()
{
    return CurrentValue;
}

double CChartPointer::GetKey()
{
    return CurrentKey;
}

void CChartPointer::UpdateView()
{
    double  delta_value  = GetValue();
    double  delta_key    = GetKey();
    CaptionPointer->setFont(QFont(Plot->font().family(), 10));
    CaptionPointer->setText(QString::number(delta_key, 'f', 3) + KeySuffix + ", " + QString::number(delta_value, 'f', 3) + " " + ValueSuffix);
    CaptionPointer->setVisible(true);

}

