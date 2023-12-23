
#ifndef CCHARTMARKER_H
#define CCHARTMARKER_H


#include <QObject>
#include "iplottool.h"

class CCahrtMarker: public IPlotTool
{
public:
    CCahrtMarker(QCustomPlot* plot, int graph_index=0);
    double GetValue();
    double GetKey();

    // IPlotTool interface
public:
    void SetColor(QColor color) override;
    void SetWorkingGraphIndex(int index) override;
    EToolType GetType() override;
    void UpdateWithMouseEvent(QMouseEvent *event) override;
    void SetVisibility(bool value) override;
    void SetGeometry(int x, int y, int width, int height) override;
    void UpdateView() override;

private:
    QCPItemText* CaptionMarker = nullptr;
    QCPItemTracer* Tracer = nullptr;
    QFont UnderlineFont;
    bool IsModifing = false;
    CCahrtMarker* DeltaMarker = nullptr;
    double CurrentKey = 0;
};

class CChartMarkerBuilder: public IToolBuilder
{
public:
    CChartMarkerBuilder(QCustomPlot* plot);
    void Update(QMouseEvent* e) override;
};

#endif // CCHARTMARKER_H
