
#ifndef CCHARTSELECTOR_H
#define CCHARTSELECTOR_H


#include <QObject>
#include "iplottool.h"


class CChartSelector : public IPlotTool
{
    Q_OBJECT
public:
    CChartSelector();
    ToolType GetType();
    void Update(QMouseEvent *event);
    void ShowSetting();
    void SetVisibility();

};

#endif // CCHARTSELECTOR_H
