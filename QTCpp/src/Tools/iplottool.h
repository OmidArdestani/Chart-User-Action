#ifndef IPLOTTOOL_H
#define IPLOTTOOL_H


#include <QMouseEvent>
#include <QObject>

#include <QCustomPlot/qcustomplot.h>

#define PLOT_TOOL_LAYER_NAME "toolsLayer"

enum class EToolType{
    Marker,
    Shape,
    Selector,
    Pointer,
    Measure
};

enum class EToolBuildMode
{
    BuildNew,
    Modify
};

class IPlotTool
{
public:
    IPlotTool(QCustomPlot* plot):Plot(plot){}
    virtual EToolType GetType() = 0;
    virtual void SetVisibility(bool value) = 0;
    virtual void SetColor(QColor color)=0;
    virtual void SetWorkingGraphIndex(int index)=0;
    virtual void SetGeometry(int x,int y,int width,int height) = 0;
    virtual void UpdateWithMouseEvent(QMouseEvent *event) = 0;
    virtual void UpdateView() = 0;

protected:
    QString KeySuffix   = "";
    QString ValueSuffix = "";
    QColor Color;
    bool Visibility = true;
    int WorkingGraphIndex = 0;
    QCustomPlot* Plot=nullptr;
};

class IPlotToolBuilder
{
public:
    IPlotToolBuilder(QCustomPlot* plot):Plot(plot){}
    virtual void UpdateWithMouseEvent(QMouseEvent *event) = 0;
    virtual void UpdateView() = 0;

protected:
    QCustomPlot* Plot=nullptr;
    std::list<IPlotTool*> ToolList;
    EToolBuildMode CurrentBuildMode = EToolBuildMode::BuildNew;
    IPlotTool* CurrentTool = nullptr;
};

#endif // IPLOTTOOL_H
