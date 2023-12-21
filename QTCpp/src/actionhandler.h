
#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H


#include <QObject>
#include "Tools/iplottool.h"
class CActionHandler : public QObject
{
    Q_OBJECT
public:
    explicit CActionHandler(QObject *parent = nullptr);
signals:

public slots:

private:
    std::map<ToolType,IPlotTool*> PlotTools;
};

#endif // ACTIONHANDLER_H
