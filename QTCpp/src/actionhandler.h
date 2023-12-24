
#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H


#include <QObject>
#include "Tools/iplottool.h"
#include <map>

class CActionHandler : public QObject
{
    Q_OBJECT
public:
    explicit CActionHandler(QCustomPlot* plot);

private:
    std::map<EToolType,IPlotToolBuilder*> PlotTools;

public slots:
    void SetPlotEvent(QMouseEvent* e);
    void UpdateView();

public:
    void SetActiveTool(EToolType mode);

private:
    EToolType ActiveToolType = EToolType::Pointer;
};

#endif // ACTIONHANDLER_H
