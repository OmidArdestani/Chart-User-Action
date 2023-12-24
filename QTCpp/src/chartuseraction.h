
#ifndef CHARTUSERACTION_H
#define CHARTUSERACTION_H


#include <QObject>
#include <QCustomPlot/qcustomplot.h>
#include <actionhandler.h>

class CChartUserAction
{
public:
    CChartUserAction(QCustomPlot* custom_plot);

    void SetMode(EToolType mode);

private:
    CActionHandler *ActionHandler = nullptr;
};

#endif // CHARTUSERACTION_H
