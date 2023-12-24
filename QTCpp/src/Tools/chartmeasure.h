
#ifndef CHARTMEASURE_H
#define CHARTMEASURE_H


#include <QObject>
#include "iplottool.h"


class CChartMeasure : public IPlotTool
{
public:
    CChartMeasure(QCustomPlot* plot, int graph_index=0);


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

#endif // CHARTMEASURE_H
