
#ifndef CHARTUSERACTION_H
#define CHARTUSERACTION_H


#include <QObject>
#include <QCustomPlot/qcustomplot.h>
#include <actionhandler.h>

namespace Ui {
class CChartUserAction;
};

class CChartUserAction: public QWidget
{
    Q_OBJECT
public:
    CChartUserAction(QCustomPlot* custom_plot,QWidget* parent=nullptr);

    void SetMode(EToolType mode);

private:
    Ui::CChartUserAction* ui = nullptr;
    CActionHandler *ActionHandler = nullptr;

private:
    void InitPlotSlots(QCustomPlot *custom_plot);
    void InitButtonsSlots();
};

#endif // CHARTUSERACTION_H
