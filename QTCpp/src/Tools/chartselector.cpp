
#include "chartselector.h"

CChartSelector::CChartSelector(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{
    AreaRect     = new QCPItemRect(Plot);
    AreaRect->topLeft->setType(QCPItemPosition::ptPlotCoords);
    AreaRect->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    AreaRect->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));

    AreaCaption = new QCPItemText(Plot);
    AreaCaption->setTextAlignment(Qt::AlignCenter | Qt::AlignTop);
    AreaCaption->position->setType(QCPItemPosition::ptPlotCoords);
    AreaCaption->setColor(Qt::cyan);
    AreaCaption->setFont(QFont(Plot->font().family(), 10, QFont::Bold));
    AreaCaption->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));

    SetWorkingGraphIndex(graph_index);
}

void CChartSelector::MouseMoveAction(QMouseEvent *event)
{
    if (FlagPlotClick)
    {
        //when click inside the area
        //decide resize or move in if
        //resize
        if (AreaResizeLower)
        {
            double   low_key_band  = Plot->xAxis->pixelToCoord(event->x());
            double   uper_key_band = AreaRange.upper;
            QCPRange new_range(low_key_band, uper_key_band);
            SetKeyRange(new_range);

            emit AreaMoved(new_range);
        }
        else if (AreaResizeUpper)
        {
            double   low_key_band  = AreaRange.lower;
            double   uper_key_band = Plot->xAxis->pixelToCoord(event->x());
            QCPRange new_range(low_key_band, uper_key_band);

            SetKeyRange(new_range);

             emit AreaMoved(new_range);
        }
        //move area
        else if(MovingArea)
        {
            int delta_x = event->x() - MousePressBegin.x();
            if(delta_x == 0) return;

            double delta_key = Plot->xAxis->pixelToCoord(delta_x);
            double   low_key_band  = TempKeyRange.lower + delta_key;
            double   uper_key_band = TempKeyRange.upper + delta_key;
            QCPRange new_range(low_key_band, uper_key_band);

            SetKeyRange(new_range);

            emit AreaMoved(new_range);
            emit SelectedArea();
        }
    }
}

void CChartSelector::MousePressAction()
{
    //is in area
    if (Visibility)
    {
        // lower size limitation
        double scale           = Plot->xAxis->range().size() / 100;
        double mouse_press_pos = Plot->xAxis->pixelToCoord(MousePressBegin.x());

        if(FirstAction)
        {
            QCPRange new_range(mouse_press_pos, mouse_press_pos + scale);
            SetKeyRange(new_range);
            SetColor(Qt::blue);

            AreaResizeUpper = true;
            return;
        }

        //resize lower
        if ((AreaRange.lower - scale < mouse_press_pos) && (AreaRange.lower + scale > mouse_press_pos))
            AreaResizeLower = true;
        //resize upper
        else if ((AreaRange.upper - scale < mouse_press_pos) && (AreaRange.upper + scale > mouse_press_pos))
            AreaResizeUpper = true;
        //moving
        else if(AreaRange.lower < mouse_press_pos && AreaRange.upper > mouse_press_pos)
        {
            MovingArea = true;
            TempKeyRange = AreaRange;
        }
    }
}

void CChartSelector::MouseReleaseAction()
{
    AreaResizeLower = false;
    AreaResizeUpper = false;
    MovingArea  = false;
    FirstAction = false;
}

void CChartSelector::UpdateWithMouseEvent(QMouseEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
        MouseMoveAction(event);
        break;
    case QEvent::MouseButtonPress:
        if ((event->button() == Qt::LeftButton) || (event->button() == Qt::RightButton))
        {
            MousePressBegin = event->pos();
            SetVisibility(true);
            MousePressAction();
            FlagPlotClick   = true;
        }
        break;
    case QEvent::MouseButtonRelease:
        if ((event->button() == Qt::LeftButton) || (event->button() == Qt::RightButton))
        {
            MouseMoveCoord = event->pos();
            MouseReleaseAction();
            FlagPlotClick = false;
        }
        break;
    default:
        break;
    }
}

void CChartSelector::SetVisibility(bool value)
{
    Visibility = value;

    AreaRect->setVisible(Visibility);
    AreaCaption->setVisible(Visibility);
}

void CChartSelector::SetColor(QColor color)
{
    this->Color = color;
    AreaRect->setPen(QPen(Color));
    AreaCaption->setColor(Color);
    color.setAlpha(45);
    AreaRect->setBrush(QBrush(color));
}

void CChartSelector::SetGeometry(int x, int y, int width, int height)
{
}

void CChartSelector::UpdateView()
{
    //set caption and rect position when area range changed
    if (qAbs(AreaRange.size()) > 0.0001 && Visibility)
    {
        AreaCaption->position->setCoords(AreaRange.center(), Plot->yAxis->pixelToCoord(20));
        AreaRect->topLeft->setCoords(AreaRange.lower, Plot->yAxis->range().upper);
        AreaRect->bottomRight->setCoords(AreaRange.upper, Plot->yAxis->range().lower);
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
    AreaRange = value;
    //
    UpdateView();
    Plot->replot();
    //    emit areaFrequencyRange(areaRange);
}
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
CChartSelectorBuilder::CChartSelectorBuilder(QCustomPlot *plot):IPlotToolBuilder(plot)
{

}

void CChartSelectorBuilder::UpdateWithMouseEvent(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CChartSelector(Plot);
        this->CurrentTool->SetVisibility(false);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        break;
    }
}

void CChartSelectorBuilder::UpdateView()
{
    if(!CurrentTool)return;

    this->CurrentTool->UpdateView();
}
