#include "cchartmarker.h"

CCahrtMarker::CCahrtMarker(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{
    // init tracer
    Tracer            = new QCPItemTracer(Plot);
    Tracer->setGraph(Plot->graph(graph_index));
    Tracer->setSize(8);
    Tracer->setStyle(QCPItemTracer::tsCircle);
    Tracer->setLayer(Plot->layer("toolsLayer"));
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

double CCahrtMarker::GetValue()
{
    return Tracer->position->value();
}

double CCahrtMarker::GetKey()
{
    return CurrentKey;
}

EToolType CCahrtMarker::GetType()
{
    return EToolType::Marker;
}

void CCahrtMarker::Update(QMouseEvent *event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        IsModifing = true;
    case QEvent::MouseMove:
        if(!IsModifing)return;

        CurrentKey = Plot->xAxis->pixelToCoord(event->x());
        Tracer->setGraphKey(CurrentKey);
        break;
    case QEvent::MouseButtonRelease:
        IsModifing = false;
        break;
    }
}

void CCahrtMarker::SetVisibility(bool value)
{
    Visibility = value;
    Tracer->setVisible(value);
    CaptionMarker->setVisible(value);
}

void CCahrtMarker::SetGeometry(int x, int y, int width, int height)
{
    CurrentKey = x;
}

void CCahrtMarker::UpdateView()
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

void CCahrtMarker::SetColor(QColor color)
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

void CCahrtMarker::SetWorkingGraphIndex(int index)
{
    WorkingGraphIndex = index;

    Tracer->setGraph(Plot->graph(index));
}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
CChartMarkerBuilder::CChartMarkerBuilder(QCustomPlot *plot):IToolBuilder(plot)
{

}

void CChartMarkerBuilder::Update(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CCahrtMarker(Plot);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        break;
    }
}
