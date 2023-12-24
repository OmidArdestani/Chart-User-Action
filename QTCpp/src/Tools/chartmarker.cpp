#include "chartmarker.h"

CChartMarker::CChartMarker(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{
    // init tracer
    Tracer            = new QCPItemTracer(Plot);
    Tracer->setGraph(Plot->graph(0/*graph_index*/));
    Tracer->setSize(8);
    Tracer->setStyle(QCPItemTracer::tsCircle);
    Tracer->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    Tracer->setInterpolating(true);

    // init font
    UnderlineFont.setUnderline(true);
    UnderlineFont.setFamily(Plot->font().family());
    UnderlineFont.setPointSize(10);

    // init caption label
    CaptionMarker = new QCPItemText(Plot);
    CaptionMarker->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
    CaptionMarker->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
    CaptionMarker->position->setType(QCPItemPosition::ptAbsolute);
    CaptionMarker->setFont(QFont(Plot->font().family(), 10));
    CaptionMarker->setVisible(false);

    // set a random color
    SetColor(QColor(QRandomGenerator::global()->bounded(100, 250),
                    QRandomGenerator::global()->bounded(100, 250), QRandomGenerator::global()->bounded(100, 250)));

    SetWorkingGraphIndex(graph_index);
}

double CChartMarker::GetValue()
{
    return Tracer->position->value();
}

double CChartMarker::GetKey()
{
    return CurrentKey;
}

EToolType CChartMarker::GetType()
{
    return EToolType::Marker;
}

void CChartMarker::UpdateWithMouseEvent(QMouseEvent *event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        IsModifing = true;
    case QEvent::MouseMove:
        if(!IsModifing)return;

        CurrentKey = Plot->xAxis->pixelToCoord(event->x());
        Tracer->setGraphKey(CurrentKey);

        Plot->layer(PLOT_TOOL_LAYER_NAME)->replot();
        break;
    case QEvent::MouseButtonRelease:
        IsModifing = false;
        break;
    }
}

void CChartMarker::SetVisibility(bool value)
{
    Visibility = value;
    Tracer->setVisible(value);
    CaptionMarker->setVisible(value);
}

void CChartMarker::SetGeometry(int x, int y, int width, int height)
{
    CurrentKey = x;
}

QCPItemText* CChartMarker::GetCaptionMarker()
{
    return CaptionMarker;
}

void CChartMarker::UpdateView()
{
    QString value_string = " value:";
    QString key_string   = " key:";
    double  delta_value  = GetValue();
    double  delta_key    = GetKey();

    if (DeltaMarker != nullptr)
    {
        delta_value  = qAbs(delta_value - DeltaMarker->GetValue());
        delta_key    = qAbs(delta_key - DeltaMarker->GetKey());
        value_string = " ∆value:";
        key_string   = " ∆key:";
        CaptionMarker->setFont(UnderlineFont);
    }
    else
    {
        CaptionMarker->setFont(QFont(Plot->font().family(), 10));
    }

    CaptionMarker->setText(key_string + QString::number(delta_key, 'f', 3) + KeySuffix + value_string + QString::number(delta_value, 'f', 1) + " " + ValueSuffix);
    CaptionMarker->setVisible(true);
}

void CChartMarker::SetColor(QColor color)
{
    this->Color = color;
    QPen pen;

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setColor(color);
    QBrush brush;

    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    Tracer->setPen(pen);
    Tracer->setBrush(brush);
    CaptionMarker->setColor(color);
}

void CChartMarker::SetWorkingGraphIndex(int index)
{
    WorkingGraphIndex = index;

    Tracer->setGraph(Plot->graph(index));
}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
CChartMarkerBuilder::CChartMarkerBuilder(QCustomPlot *plot):IPlotToolBuilder(plot)
{

}

void CChartMarkerBuilder::UpdateWithMouseEvent(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CChartMarker(Plot);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        this->CurrentTool->SetVisibility(true);
        break;
    }
}

void CChartMarkerBuilder::UpdateView()
{
    if(!CurrentTool)return;

    this->CurrentTool->UpdateView();

    UpdateMarkersCaption();
}


void CChartMarkerBuilder::UpdateMarkersCaption()
{
    double x = Plot->axisRect()->margins().left();

    for (auto item = ToolList.cbegin(); item != ToolList.cend() ; ++item)
    {
        QCPItemText* caption = static_cast<CChartMarker*>(*item)->GetCaptionMarker();

        QFontMetrics fm(caption->font());

        caption->position->setPixelPosition(QPointF(x, Plot->axisRect()->margins().top() + 20));
        x += fm.lineWidth();
    }
}
