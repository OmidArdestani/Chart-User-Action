
#include "chartselector.h"

CChartSelector::CChartSelector(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot),
    WorkingGraphIndex(graph_index)
{
    this->parent = parent;
    areaRect     = new QCPItemRect(parent);
    areaRect->topLeft->setType(QCPItemPosition::ptPlotCoords);
    areaRect->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    //
    areaCaption = new QCPItemText(parent);
    areaCaption->setTextAlignment(Qt::AlignCenter | Qt::AlignTop);
    //  areaCaption->setPositionAlignment(Qt::AlignCenter|Qt::AlignTop);
    areaCaption->position->setType(QCPItemPosition::ptPlotCoords);
    areaCaption->setColor(Qt::cyan);
    areaCaption->setFont(QFont(parent->font().family(), 10, QFont::Bold));

    //set layer to caption &rect
    areaCaption->setLayer(parent->layer(PLOT_TOOL_LAYER_NAME));
    areaRect->setLayer(parent->layer(PLOT_TOOL_LAYER_NAME));
    areaCaption->setVisible(false);
    areaRect->setVisible(false);

}


EToolType CChartSelector::GetType()
{
    return EToolType::Selector;
}

void CChartSelector::MouseMoveAction()
{
    if (flagPlotClick)
    {
        {
            //when click inside the area
            //decide resize or move in if
            if (indexSearchArea > -1)
            {
                //resize
                if (areaResizeLower)
                {
                    double deltaKey = CPlot->xAxis->pixelToCoord(mouseMove.x()) -
                                      CPlot->xAxis->pixelToCoord(mousePressBegin.x());
                    double   lowKeyBand  = tempKeyRange.lower + deltaKey;
                    double   uperKeyBand = tempKeyRange.upper;
                    QCPRange newrange(lowKeyBand, uperKeyBand);
                    toolList->areaList[indexSearchArea]->setKeyRange(newrange);
                    emit areaMoved(newrange, indexSearchArea);
                }
                else if (areaResizeUpper)
                {
                    double deltaKey = CPlot->xAxis->pixelToCoord(mouseMove.x()) -
                                      CPlot->xAxis->pixelToCoord(mousePressBegin.x());
                    double   lowKeyBand  = tempKeyRange.lower;
                    double   uperKeyBand = tempKeyRange.upper + deltaKey;
                    QCPRange newrange(lowKeyBand, uperKeyBand);
                    toolList->areaList[indexSearchArea]->setKeyRange(newrange);
                    emit areaMoved(newrange, indexSearchArea);
                }
                //move area
                else
                {
                    double deltaKey = CPlot->xAxis->pixelToCoord(mouseMove.x()) -
                                      CPlot->xAxis->pixelToCoord(mousePressBegin.x());
                    double   lowKeyBand  = tempKeyRange.lower + deltaKey;
                    double   uperKeyBand = tempKeyRange.upper + deltaKey;
                    QCPRange newrange(lowKeyBand, uperKeyBand);
                    toolList->areaList[indexSearchArea]->setKeyRange(newrange);
                    emit areaMoved(newrange, indexSearchArea);
                    //               emit selectedArea(newrange, indexSearchArea);
                }
            }
        }
    }
}

void CChartSelector::MousePressAction()
{
    {
        double   keyLowBand  = Plot->xAxis->pixelToCoord(MousePressBegin.x());
        double   keyUperBand = Plot->xAxis->pixelToCoord(MouseMoveCoord.x());
        QCPRange newKeyRange(keyLowBand, keyUperBand);
        areaRange = newKeyRange;
        //remove area if less than a constant value
        double value = CPlot->xAxis->range().size() / 100 * 10;
        if (newKeyRange.size() < value)
        {
            // toolList->areaList[toolList->areaList.count() - 1]->destroyed();
        }
    }
    //is in area
    if (Visibility)
    {
        //resize lower
        double scale         = Plot->xAxis->range().size() / 100;
        double mousePressPos = Plot->xAxis->pixelToCoord(MousePressBegin.x());
        if ((areaRange.lower - scale < mousePressPos) &&
            (areaRange.lower + scale > mousePressPos))
        {
            areaResizeLower = true;
        }
        //resize upper
        else if ((areaRange.upper - scale < mousePressPos) &&
                 (areaRange.upper + scale > mousePressPos))
        {
            areaResizeUpper = true;
        }
        //move area
        tempKeyRange = toolList->areaList[indexSearchArea]->getKeyRange();
    }
}


void CChartSelector::MouseReleaseAction()
{
    flagNewArea     = false;
    areaResizeLower = false;
    areaResizeUpper = false;
}

void CChartSelector::UpdateWithMouseEvent(QMouseEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::MouseButtonPress:
        if ((event->button() == Qt::LeftButton) || (event->button() == Qt::RightButton))
            MousePressAction();
        break;
    case QEvent::MouseButtonRelease:
        if ((event->button() == Qt::LeftButton) || (event->button() == Qt::RightButton))
            MouseReleaseAction();
        break;
    default:
        break;
    }
}

void CChartSelector::SetVisibility(bool value)
{
    areaVisibility = value;
    if (areaVisibility == true)
    {
        areaRect->setVisible(true);
        areaCaption->setVisible(true);
    }
    else
    {
        areaRect->setVisible(false);
        areaCaption->setVisible(false);
    }
}

void CChartSelector::SetColor(QColor color)
{
    this->Color = color;
    areaRect->setPen(QPen(Color));
    areaCaption->setColor(Color);
    color.setAlpha(45);
    areaRect->setBrush(QBrush(color));
}

void CChartSelector::SetWorkingGraphIndex(int index)
{
}

void CChartSelector::SetGeometry(int x, int y, int width, int height)
{
}

void CChartSelector::UpdateView()
{
    //set caption and rect position when area range changed
    if (qAbs(areaRange.size()) > 0.0001)
    {
        areaCaption->position->setCoords(areaRange.center(), parent->yAxis->pixelToCoord(20));
        areaRect->topLeft->setCoords(areaRange.lower, parent->yAxis->range().upper);
        areaRect->bottomRight->setCoords(areaRange.upper, parent->yAxis->range().lower);
        areaRect->setVisible(true);
    }
}

void CChartSelector::SetKeyRange(QCPRange value)
{
    if (value.lower > value.upper)
    {
        double temp = value.lower;
        value.lower = value.upper;
        value.upper = temp;
    }
    areaRange = value;
    areaRect->setVisible(true);
    areaCaption->setVisible(true);
    //
    UpdateView();
    parent->replot();
    //    emit areaFrequencyRange(areaRange);
}
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
CChartSelectorBuilder::CChartSelectorBuilder(QCustomPlot *plot)
{

}

void CChartSelectorBuilder::UpdateWithMouseEvent(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CChartSelector(Plot);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        this->CurrentTool->SetVisibility(true);
        break;
    }
}

void CChartSelectorBuilder::UpdateView()
{
    if(!CurrentTool)return;

    this->CurrentTool->UpdateView();
}
