
#ifndef CHARTUSERACTION_H
#define CHARTUSERACTION_H


#include <QObject>
#include <QCustomPlot/qcustomplot.h>
#include <actionhandler.h>

class CChartUserAction : public QObject
{
    Q_OBJECT
public:
    explicit CChartUserAction(QObject *parent = nullptr);
    CChartUserAction(QCustomPlot *custom_plot);
public slots:
    void OnMouseDoubleClick(QMouseEvent *event);
    void OnMouseRelease(QMouseEvent *event);
    void OnMousePress(QMouseEvent *event);
    void OnMouseMove(QMouseEvent *event);
    void OnMouseWheel(QMouseEvent *event);

signals:
private:
    CActionHandler *ActionHandler = nullptr;
};

#endif // CHARTUSERACTION_H
