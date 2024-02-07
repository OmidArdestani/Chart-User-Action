
#ifndef CHARTSELECTOR_H
#define CHARTSELECTOR_H


#include <QObject>
#include "iplottool.h"


class CChartSelector : public IPlotTool
{
public:
    CChartSelector(QCustomPlot* plot, int graph_index=0);


    // IPlotTool interface
public:
    EToolType GetType() override;
    void UpdateWithMouseEvent(QMouseEvent *event) override;
    void SetVisibility(bool value) override;
    void SetColor(QColor color) override;
    void SetWorkingGraphIndex(int index) override;
    void SetGeometry(int x, int y, int width, int height) override;
    void UpdateView() override;

private:
    void SetKeyRange(QCPRange value);

private:

    QColor Color        = Qt::white;
    QString caption     = "";
    bool areaVisibility = true;

    bool flagNewArea                 = false;
    bool areaResizeLower             = false;
    bool areaResizeUpper             = false;
    bool flagPlotClick               = false;

    QCPRange areaRange;
    QCPRange tempKeyRange;

    QCustomPlot *parent      = nullptr;
    QCPItemText *areaCaption = nullptr;
    QCPItemRect *areaRect    = nullptr;

    QPoint MousePressBegin = QPoint(0, 0);
    QPointF MouseMoveCoord = QPointF(0, 0);

private:
    void MousePressAction();
    void MouseReleaseAction();
    void MouseMoveAction(QMouseEvent *event);
};

class CChartSelectorBuilder: public IPlotToolBuilder
{
public:
    CChartSelectorBuilder(QCustomPlot* plot);
    void UpdateWithMouseEvent(QMouseEvent* e) override;
    void UpdateView() override;
};

#endif // CHARTSELECTOR_H
