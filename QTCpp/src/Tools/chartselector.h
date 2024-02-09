
#ifndef CHARTSELECTOR_H
#define CHARTSELECTOR_H


#include <QObject>
#include "iplottool.h"


class CChartSelector : public IPlotTool
{
    Q_OBJECT
public:
    CChartSelector(QCustomPlot* plot, int graph_index=0);

    // IPlotTool interface
public:
    EToolType GetType() override{return EToolType::Selector;}
    void UpdateWithMouseEvent(QMouseEvent *event) override;
    void SetVisibility(bool value) override;
    void SetColor(QColor color) override;
    void SetGeometry(int x, int y, int width, int height) override;
    void UpdateView() override;
    void SetKeyRange(QCPRange value);

private:
    QColor Color        = Qt::white;
    QString caption     = "";

    bool AreaResizeLower = false;
    bool AreaResizeUpper = false;
    bool MovingArea      = false;
    bool FlagPlotClick   = false;
    bool FirstAction     = true;

    QCPRange AreaRange;
    QCPRange TempKeyRange;

    QCPItemText *AreaCaption = nullptr;
    QCPItemRect *AreaRect    = nullptr;

    QPoint MousePressBegin = QPoint(0, 0);
    QPointF MouseMoveCoord = QPointF(0, 0);

private:
    void MousePressAction();
    void MouseReleaseAction();
    void MouseMoveAction(QMouseEvent *event);

signals:
    void AreaMoved(QCPRange newrange);
    void SelectedArea();
};

class CChartSelectorBuilder: public IPlotToolBuilder
{
public:
    CChartSelectorBuilder(QCustomPlot* plot);
    void UpdateWithMouseEvent(QMouseEvent* e) override;
    void UpdateView() override;
};

#endif // CHARTSELECTOR_H
