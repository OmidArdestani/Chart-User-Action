
#ifndef CHARTMARKER_H
#define CHARTMARKER_H


#include <QObject>
#include "iplottool.h"

class CChartMarker: public IPlotTool
{
public:
    CChartMarker(QCustomPlot* plot, int graph_index=0);
    double GetValue();
    double GetKey();

    // IPlotTool interface
public:
    void SetColor(QColor color) override;
    void SetWorkingGraphIndex(int index) override;
    EToolType GetType() override;
    void UpdateWithMouseEvent(QMouseEvent *event) override;
    void UpdateView() override;
    void SetVisibility(bool value) override;
    void SetGeometry(int x, int y, int width, int height) override;

    QCPItemText* GetCaptionMarker();

private:
    QCPItemText* CaptionMarker = nullptr;
    QCPItemTracer* Tracer = nullptr;
    QFont UnderlineFont;
    bool IsModifing = true;
    CChartMarker* DeltaMarker = nullptr;
    double CurrentKey = 0;
};

class CChartMarkerBuilder: public IPlotToolBuilder
{
public:
    CChartMarkerBuilder(QCustomPlot* plot);
    void UpdateWithMouseEvent(QMouseEvent* e) override;
    void UpdateView() override;

private:
    void UpdateMarkersCaption();
};

#endif // CHARTMARKER_H
