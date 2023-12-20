
#ifndef CCHARTPOINTER_H
#define CCHARTPOINTER_H


#include <QObject>
#include "iplottool.h"


class CChartPointer: public IPlotTool
{
    Q_OBJECT
public:
    CChartPointer();
    ToolType GetType();
    void Update(QMouseEvent *event);
    void ShowSetting();
    void SetVisibility();

};

#endif // CCHARTPOINTER_H
