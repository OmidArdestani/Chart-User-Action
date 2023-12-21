
#ifndef CCHARTMEASURE_H
#define CCHARTMEASURE_H


#include <QObject>
#include "iplottool.h"


class CChartMeasure : public IPlotTool
{
    Q_OBJECT
public:
    explicit CChartMeasure(QObject *parent = nullptr);
    ToolType GetType();
    void Update(QMouseEvent *event);
    void ShowSetting();
    void SetVisibility();

signals:

};

#endif // CCHARTMEASURE_H
