
#include "chartmeasure.h"

CChartMeasure::CChartMeasure(QCustomPlot* plot,int graph_index)
    : IPlotTool(plot)
{
    MinValueLabel = new QLabel(Plot);
    MinKeyLabel   = new QLabel(Plot);
    MaxKeyLabel   = new QLabel(Plot);
    MaxValueLabel = new QLabel(Plot);

    MeasureRect    = new QCPItemRect(Plot);

    MeasureLineHor = new QCPItemLine(Plot);
    MeasureLineVer = new QCPItemLine(Plot);

    MeasureCaption = new QCPItemText(Plot);

    ValueMeasureBegin = new QCPItemPixmap(Plot);
    ValueMeasureEnd   = new QCPItemPixmap(Plot);
    KeyMeasureBegin   = new QCPItemPixmap(Plot);
    KeyMeasureEnd     = new QCPItemPixmap(Plot);

    MaxValueLabel->setVisible(false);
    MaxKeyLabel->setVisible(false);
    MinValueLabel->setVisible(false);
    MinKeyLabel->setVisible(false);

    KeyMeasureBegin->setClipToAxisRect(false);
    KeyMeasureEnd->setClipToAxisRect(false);
    ValueMeasureBegin->setClipToAxisRect(false);
    ValueMeasureEnd->setClipToAxisRect(false);

    MeasureRect->topLeft->setType(QCPItemPosition::ptPlotCoords);
    MeasureRect->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    MeasureCaption->position->setType(QCPItemPosition::ptPlotCoords);
    //
    MeasureCaption->setColor(Qt::white);
    MeasureCaption->setFont(QFont(Plot->font().family(), 10));

    Font = new QFontMetrics(MeasureCaption->font());

    //set layer to caption & rect
    MeasureCaption->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    MeasureRect->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    MeasureLineHor->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    MeasureLineVer->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    MeasureCaption->setLayer(Plot->layer(PLOT_TOOL_LAYER_NAME));
    MeasureCaption->setVisible(false);
    MeasureRect->setVisible(false);
    MeasureLineHor->setVisible(false);
    MeasureLineVer->setVisible(false);
}

EToolType CChartMeasure::GetType()
{
    return EToolType::Measure;
}


void CChartMeasure::DrawPlotText(QCPItemPixmap *p, QSize boxSize, QString str, QPen textPen, QBrush bckColor, QPointF pos)
{
    QRect fontBoundingRect = QRect(0, 0, boxSize.width(), boxSize.height());
    // then create a square pixmap that will contain the complete text, even if rotate and set its backgroud transparent
    QPixmap *piz = new QPixmap(fontBoundingRect.width(), fontBoundingRect.height());//a square of side "width"

    piz->fill(QColor::fromRgb(0, 0, 0, 0));
    //now paint on pixmap with the desired rotation, color and bckground (here I've set a padding of the text of 4 pixels, can be brought in the function arguments)
    QPainter painter(piz);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(textPen);
    painter.setBrush(bckColor);
    painter.drawRoundedRect(fontBoundingRect, 4, 4);
    painter.drawText(fontBoundingRect, str, Qt::AlignCenter | Qt::AlignHCenter);
    p->setPixmap(*piz);
    p->topLeft->setPixelPosition(pos);
}

void CChartMeasure::SetKeyRange(const QCPRange& key)
{
    MeasureKey = key;
    SetVisibility(true);
    SetCaption(" ∆K:" + QString::number(MeasureKey.size(), 'f', 2) + " " + KeySuffix + "\n∆V:" +
               QString::number(MeasureValue.size(), 'f', 2) + " " + ValueSuffix + "  ");
    UpdateView();
    //check if  measureKey is smallarea so dont make arrow at line endingd
    double keyDelta = qAbs(Plot->xAxis->coordToPixel(MeasureKey.upper) - Plot->xAxis->coordToPixel(MeasureKey.lower));

    if (keyDelta < 40)
    {
        MeasureLineHor->setTail(QCPLineEnding::esNone);
        MeasureLineHor->setHead(QCPLineEnding::esNone);
    }
}


void CChartMeasure::SetValueRange(QCPRange range)
{
    MeasureValue = range;

    //we use setrange of area for frquenc here we must have power range
    SetVisibility(true);

    //arecaption.text is inside the setLabel here we set position
    SetCaption("\a\a\a" + QString::number(MeasureKey.size(), 'f', 2) + " " + KeySuffix + "\a\a\n\a\a"
               + QString::number(MeasureValue.size(), 'f', 2) + " " + ValueSuffix);
    UpdateView();

    //check if  measureValue is smallarea so dont make arrow at line endingd
    double valueDelta = qAbs(Plot->yAxis->coordToPixel(MeasureValue.upper) - Plot->yAxis->coordToPixel(MeasureValue.lower));

    if (valueDelta < 40)
    {
        MeasureLineVer->setTail(QCPLineEnding::esNone);
        MeasureLineVer->setHead(QCPLineEnding::esNone);
    }
}

void CChartMeasure::SetCaption(QString value)
{
    Caption = value;
    MeasureCaption->setText(value);
}

void CChartMeasure::SetKeyArrow(HorArrowSituation arrow)
{
    if (arrow == ALeft)
    {
        MeasureLineHor->setTail(QCPLineEnding::esSpikeArrow);
        MeasureLineHor->setHead(QCPLineEnding::esNone);
    }
    else
    {
        MeasureLineHor->setHead(QCPLineEnding::esSpikeArrow);
        MeasureLineHor->setTail(QCPLineEnding::esNone);
    }
}

void CChartMeasure::setValueArrow(VerArrowSituation arrow)
{
    if (arrow == ATop)
    {
        MeasureLineVer->setHead(QCPLineEnding::esSpikeArrow);
        MeasureLineVer->setTail(QCPLineEnding::esNone);
        SetColor(QColor(33, 150, 170));
        IsCaptionBottom = false;
    }
    else
    {
        MeasureLineVer->setTail(QCPLineEnding::esSpikeArrow);
        MeasureLineVer->setHead(QCPLineEnding::esNone);
        SetColor(QColor(239, 83, 80));
        IsCaptionBottom = true;
    }
}

void CChartMeasure::BeginDrawBox(QPoint pos)
{
    MousePressBegin = pos;
    // maxminMeasure = true;
    // init sizeBox
    QSize   size_box;
    size_box.setWidth(35);
    size_box.setHeight(15);

    QSize size_box_x_axis;
    size_box_x_axis.setWidth(45);
    size_box_x_axis.setHeight(20);

    QPointF my_point;
    my_point.setX(Plot->axisRect()->margins().left() - size_box.width());
    my_point.setY(MousePressBegin.y() - size_box.height() / 2);

    DrawPlotText(ValueMeasureBegin, size_box, QString::number(Plot->yAxis->pixelToCoord(MousePressBegin.y()), 'f', ValuePrecision), QPen(QColor(200, 200, 200)),
                 QBrush(QColor(33, 150, 170)), my_point);

    //key
    my_point.setX(MousePressBegin.x() - size_box_x_axis.height());
    my_point.setY(Plot->height() - (Plot->axisRect()->margins().bottom()));

    DrawPlotText(KeyMeasureBegin, size_box_x_axis, QString::number(Plot->xAxis->pixelToCoord(MousePressBegin.x()), 'f', KeyPrecision), QPen(QColor(200, 200, 200)),
                 QBrush(QColor(33, 150, 170)), my_point);

    //part of begining & ending key and value
    KeyMeasureBegin->setVisible(true);
    ValueMeasureBegin->setVisible(true);
}

void CChartMeasure::MouseLeftClickUpdate(QMouseEvent *e)
{
    if (Visibility && !UpdateFlag)
    {
        UpdateFlag = true;
        BeginDrawBox(e->pos());
        return;
    }
    //last click for end measure
    UpdateFlag = false;
}

void CChartMeasure::UpdateDrawBox(QPoint pos)
{
    // initialize arrow
    // init key arrow
    if (Plot->xAxis->pixelToCoord(MousePressBegin.x()) > Plot->xAxis->pixelToCoord(pos.x()))
        SetKeyArrow(CChartMeasure::ALeft);
    else
        SetKeyArrow(CChartMeasure::ARight);

    // init value arrow
    if (Plot->yAxis->pixelToCoord(MousePressBegin.y()) > Plot->yAxis->pixelToCoord(pos.y()))
        setValueArrow(CChartMeasure::ABottom);
    else
        setValueArrow(CChartMeasure::ATop);

    // set key&value range for measure
    SetValueRange(QCPRange(Plot->yAxis->pixelToCoord(MousePressBegin.y()), Plot->yAxis->pixelToCoord(pos.y())));
    SetKeyRange(QCPRange(Plot->xAxis->pixelToCoord(MousePressBegin.x()), Plot->xAxis->pixelToCoord(pos.x())));

    QPointF mouse_move_coord;
    mouse_move_coord.setX(Plot->xAxis->pixelToCoord(pos.x()));
    mouse_move_coord.setY(Plot->yAxis->pixelToCoord(pos.y()));

    // set value & key ending measure caption
    if ((mouse_move_coord.x() >= Plot->xAxis->range().lower) && (mouse_move_coord.x() <= Plot->xAxis->range().upper) &&
        (mouse_move_coord.y() >= Plot->yAxis->range().lower) && (mouse_move_coord.y() <= Plot->yAxis->range().upper))
    {
        // crosshair mode
        // build sizeBox

        QSize   sizeBox;
        sizeBox.setWidth(35);
        sizeBox.setHeight(15);

        QSize sizeBoxXaxis;
        sizeBoxXaxis.setWidth(45);
        sizeBoxXaxis.setHeight(20);

        //part of begining & ending key and value
        KeyMeasureEnd->setVisible(true);
        ValueMeasureEnd->setVisible(true);

        //value measure
        QPointF myPoint;
        myPoint.setX(Plot->axisRect()->margins().left() - sizeBox.width());
        myPoint.setY(pos.y() - sizeBox.height() / 2);

        if (IsCaptionBottom)
        {
            DrawPlotText(ValueMeasureEnd, sizeBox, QString::number(MouseMoveCoord.y(), 'f', ValuePrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(239, 83, 80)), myPoint);

            DrawPlotText(KeyMeasureEnd, sizeBoxXaxis, QString::number(MouseMoveCoord.x(), 'f', KeyPrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(239, 83, 80)), QPointF(pos.x() - sizeBoxXaxis.height(),
                                 Plot->height() - (Plot->axisRect()->margins().bottom())));

            DrawPlotText(ValueMeasureBegin, sizeBox, QString::number(Plot->yAxis->pixelToCoord(MousePressBegin.y()), 'f', ValuePrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(239, 83, 80)), QPointF(Plot->axisRect()->margins().left() - sizeBox.width(),
                                 MousePressBegin.y() - sizeBox.height() / 2));

            DrawPlotText(KeyMeasureBegin, sizeBoxXaxis, QString::number(Plot->xAxis->pixelToCoord(MousePressBegin.x()), 'f', KeyPrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(239, 83, 80)), QPointF(MousePressBegin.x() - sizeBoxXaxis.height(),
                                 Plot->height() - (Plot->axisRect()->margins().bottom())));
        }
        else
        {
            DrawPlotText(ValueMeasureEnd, sizeBox, QString::number(MouseMoveCoord.y(), 'f', ValuePrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(33, 150, 170)), myPoint);

            DrawPlotText(KeyMeasureEnd, sizeBoxXaxis, QString::number(MouseMoveCoord.x(), 'f', KeyPrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(33, 150, 170)), QPointF(pos.x() - sizeBoxXaxis.height(),
                                 Plot->height() - (Plot->axisRect()->margins().bottom())));

            myPoint.setX(Plot->axisRect()->margins().left() - sizeBox.width());
            myPoint.setY(MousePressBegin.y() - sizeBox.height() / 2);

            DrawPlotText(ValueMeasureBegin, sizeBox, QString::number(Plot->yAxis->pixelToCoord(MousePressBegin.y()), 'f', ValuePrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(33, 150, 170)), myPoint);

            DrawPlotText(KeyMeasureBegin, sizeBoxXaxis, QString::number(Plot->xAxis->pixelToCoord(MousePressBegin.x()), 'f', KeyPrecision), QPen(QColor(200, 200, 200)),
                         QBrush(QColor(33, 150, 170)), QPointF(MousePressBegin.x() - sizeBoxXaxis.height(),
                                 Plot->height() - (Plot->axisRect()->margins().bottom())));
        }
    }
    else
    {
        KeyMeasureEnd->setVisible(false);
        ValueMeasureEnd->setVisible(false);
    }
}

void CChartMeasure::MouseMoveUpdate(QMouseEvent *e)
{
    if (!(Visibility && UpdateFlag)) return;

    UpdateDrawBox(e->pos());
}

void CChartMeasure::UpdateWithMouseEvent(QMouseEvent *event)
{
    switch(event->type())
    {
    case QMouseEvent::MouseButtonPress:
    {
        if(event->button() == Qt::LeftButton)
        {
            MouseLeftClickUpdate(event);
            UpdateView();
            SetVisibility(true);
        }
    }
    case QMouseEvent::MouseMove:
    {
        MouseMoveUpdate(event);
        break;
    }
    }
}

void CChartMeasure::SetVisibility(bool value)
{
    MeasureRect->setVisible(value);
    MeasureLineHor->setVisible(value);
    MeasureLineVer->setVisible(value);
    MeasureCaption->setVisible(value);

    MaxValueLabel->setVisible(value);
    MaxKeyLabel->setVisible(value);

    MinValueLabel->setVisible(value);
    MinKeyLabel->setVisible(value);
}

void CChartMeasure::SetColor(QColor color)
{
    this->Color = color;
    MeasureLineHor->setPen(color);
    MeasureLineVer->setPen(color);
    MeasureCaption->setBrush(color);

    MinValueLabel->setStyleSheet("background-color:" + color.name());
    MinKeyLabel->setStyleSheet("background-color:" + color.name());
    MaxKeyLabel->setStyleSheet("background-color:" + color.name());
    MaxValueLabel->setStyleSheet("background-color:" + color.name());

    QColor light_color(Color.red(), Color.green(), Color.blue(), 70);
    MeasureRect->setBrush(light_color);
    MeasureRect->setPen(light_color);
}

void CChartMeasure::SetWorkingGraphIndex(int index)
{
}

void CChartMeasure::SetGeometry(int x, int y, int width, int height)
{
    BeginDrawBox(QPoint(x, y));
    UpdateDrawBox(QPoint(x + width, y + height));
    UpdateView();
}

void CChartMeasure::UpdateView()
{
    if (!(Visibility && UpdateFlag)) return;
    // if (qAbs(MeasureValue.size()) < 0.0001) return;

    //caption position
    //mcHeight=height of measure caption
    int mcHeight = Font->boundingRect(QRect(0, 0, 0, 0), 0, MeasureCaption->text()).height();
    if (IsCaptionBottom)  //iscaptionButtom=true   caption is in buttom
    {
        //caption near xaxis rect
        if (Plot->yAxis->coordToPixel(MeasureValue.lower) > Plot->yAxis->coordToPixel(Plot->yAxis->range().lower) - mcHeight - (mcHeight / 20))
        {
            MeasureCaption->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);
            MeasureCaption->position->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower,
                                                Plot->yAxis->range().lower);
        }
        else     // everyWhere
        {
            MeasureCaption->setPositionAlignment(Qt::AlignTop | Qt::AlignCenter);
            MeasureCaption->position->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower,
                                                MeasureValue.lower);
        }
    }
    else    //iscaptionButtom=false   caption is in top
    {
        //caption near xaxis2 rect
        if (Plot->yAxis->coordToPixel(MeasureValue.upper) < +Plot->axisRect()->margins().top() + mcHeight + (mcHeight / 20))
        {
            MeasureCaption->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);
            MeasureCaption->position->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower,
                                                Plot->yAxis->range().upper);
        }
        else     // everyWhere
        {
            MeasureCaption->setPositionAlignment(Qt::AlignBottom | Qt::AlignLeft);
            MeasureCaption->position->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower,
                                                MeasureValue.upper);
        }
    }
    //show max min in measure
    MaxValueLabel->setVisible(true);
    MaxKeyLabel->setVisible(true);
    MinValueLabel->setVisible(true);
    MinKeyLabel->setVisible(true);

    MinValueLabel->setGeometry(Plot->xAxis->coordToPixel(qAbs(Plot->xAxis->range().lower - Plot->xAxis->range().upper) / 2 + Plot->xAxis->range().lower)
                               , Plot->yAxis->coordToPixel(Plot->yAxis->range().lower) - 20
                               , 160, 20);

    MinKeyLabel->setGeometry(Plot->xAxis->coordToPixel(qAbs(Plot->xAxis->range().lower - Plot->xAxis->range().upper) / 2 + Plot->xAxis->range().lower) + 160
                             , Plot->yAxis->coordToPixel(Plot->yAxis->range().lower) - 20
                             , 120, 20);

    MaxKeyLabel->setGeometry(Plot->xAxis->coordToPixel(qAbs(Plot->xAxis->range().lower - Plot->xAxis->range().upper) / 2 + Plot->xAxis->range().lower) - 130
                             , Plot->yAxis->coordToPixel(Plot->yAxis->range().lower) - 20
                             , 120, 20);

    MaxValueLabel->setGeometry(Plot->xAxis->coordToPixel(qAbs(Plot->xAxis->range().lower - Plot->xAxis->range().upper) / 2 + Plot->xAxis->range().lower) - 290
                               , Plot->yAxis->coordToPixel(Plot->yAxis->range().lower) - 20
                               , 160, 20);

    //rect position
    MeasureRect->topLeft->setCoords(MeasureKey.lower, MeasureValue.upper);
    MeasureRect->bottomRight->setCoords(MeasureKey.upper, MeasureValue.lower);

    //line position
    MeasureLineHor->start->setCoords(MeasureKey.lower, (MeasureValue.upper - MeasureValue.lower) / 2 + MeasureValue.lower);
    MeasureLineHor->end->setCoords(MeasureKey.upper, (MeasureValue.upper - MeasureValue.lower) / 2 + MeasureValue.lower);
    MeasureLineVer->start->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower, MeasureValue.lower);
    MeasureLineVer->end->setCoords((MeasureKey.upper - MeasureKey.lower) / 2 + MeasureKey.lower, MeasureValue.upper);

    //maxmin
    QPointF max, min;
    CalculateMaxmin(MeasureKey, max, min);
    SetMaxminCaption(max, min);
}

void CChartMeasure::CalculateMaxmin(QCPRange newRange, QPointF& maxx, QPointF& minn)
{
    if ((Plot == nullptr) || (newRange.size() == 0)) return;

    QCPGraphDataContainer::const_iterator begin;
    QCPGraphDataContainer::const_iterator end;

    begin = Plot->graph(WorkingGraphIndex)->data()->findBegin(newRange.lower);
    end   = Plot->graph()->data()->findEnd(newRange.upper);

    if ((begin == nullptr) || (end == nullptr)) return;

    const QCPGraphData maxData = *std::max_element(begin,
                                                   end,
                                                   [ = ](QCPGraphData a, QCPGraphData b) {
                                                       return a.value < b.value;
                                                   });

    const QCPGraphData minData = *std::min_element(begin, end, [](QCPGraphData a, QCPGraphData b) {
        return a.value < b.value;
    });

    maxx = QPointF(maxData.key, maxData.value);
    minn = QPointF(minData.key, minData.value);

    const double mean = std::accumulate(begin,
                                        end,
                                        .0,
                                        [](double a, QCPGraphData b) {
                                            return a + b.value;
                                        }) / std::distance(begin, end);

    std::vector<double> diff(std::distance(begin, end));
    std::transform(begin, end, diff.begin(), [mean](QCPGraphData x) {
        return x.value - mean;
    });
}

void CChartMeasure::SetMaxminCaption(QPointF max, QPointF min)
{
    MinValueLabel->setText("Min:Value=" + (QString::number(min.y()) + ValueSuffix).leftJustified(15, ' ', true));
    MinKeyLabel->setText("Key=" + (QString::number(min.x()) + KeySuffix));
    MaxKeyLabel->setText("Key=" + (QString::number(max.x()) + KeySuffix));
    MaxValueLabel->setText("Max:Value=" + (QString::number(max.y()) + ValueSuffix));
}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
CChartMeasureBuilder::CChartMeasureBuilder(QCustomPlot* plot):
    IPlotToolBuilder(plot)
{
}


void CChartMeasureBuilder::UpdateWithMouseEvent(QMouseEvent *e)
{
    switch(this->CurrentBuildMode)
    {
    case EToolBuildMode::BuildNew:
        this->CurrentTool = new CChartMeasure(Plot);

        this->ToolList.push_back(CurrentTool);

        this->CurrentBuildMode = EToolBuildMode::Modify;

    case EToolBuildMode::Modify:
        this->CurrentTool->UpdateWithMouseEvent(e);
        break;
    }
}

void CChartMeasureBuilder::UpdateView()
{
    if(!CurrentTool)return;

    this->CurrentTool->UpdateView();
}
