
#ifndef CHARTPOINTER_H
#define CHARTPOINTER_H


#include <QObject>
#include "iplottool.h"
#include <QPointF>

class CChartPointer: public IPlotTool
{
public:
    CChartPointer(QCustomPlot* plot, int graph_index=0);
    double GetValue();
    double GetKey();

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
    QCPItemLine *HorizontalLine = nullptr;
    QCPItemLine *VerticalLine = nullptr;
    QCPItemText* CaptionPointer = nullptr;
    QCPItemRect* CaptionBackground = nullptr;

    double CurrentKey = 0;
    double CurrentValue = 0;
    QFont UnderlineFont;
    QPointF captionPosition;
    QPointF bottomRight;
};

class CChartPointerBuilder: public IPlotToolBuilder
{
public:
    CChartPointerBuilder(QCustomPlot* plot);
    void UpdateWithMouseEvent(QMouseEvent* e) override;
    void UpdateView() override;
};
#endif // CHARTPOINTER_H
