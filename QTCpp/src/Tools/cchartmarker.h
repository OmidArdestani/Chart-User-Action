
#ifndef CCHARTMARKER_H
#define CCHARTMARKER_H


#include <QObject>
#include "iplottool.h"

class Marker : public IPlotTool
{
    Q_OBJECT
public:
    explicit Marker(QObject *parent = nullptr);
    ToolType GetType();
    void Update(QMouseEvent *event);
    void ShowSetting();
    void SetVisibility();

signals:

};

#endif // CCHARTMARKER_H
