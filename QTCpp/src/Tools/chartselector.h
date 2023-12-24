
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
};

#endif // CHARTSELECTOR_H
