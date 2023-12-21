
#ifndef IPLOTTOOL_H
#define IPLOTTOOL_H


#include <QMouseEvent>
#include <QObject>

enum class ToolType{
    Marker,
    Shape,
    Selector,
    Pointer,
    Measure
};

class IPlotTool
{
public:
    ToolType GetType() = 0;
    void Update(QMouseEvent *event) = 0;
    void ShowSetting() = 0;
    void SetVisibility() = 0;
};

#endif // IPLOTTOOL_H
