
#ifndef CCHARTSHAPE_H
#define CCHARTSHAPE_H


#include <QObject>
#include "iplottool.h"


class CChartShape : public IPlotTool
{
    Q_OBJECT
public:
    CChartShape();
    ToolType GetType();
    void Update(QMouseEvent *event);
    void ShowSetting();
    void SetVisibility();

};

#endif // CCHARTSHAPE_H
