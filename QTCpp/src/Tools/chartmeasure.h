
#ifndef CHARTMEASURE_H
#define CHARTMEASURE_H


#include <QObject>
#include "iplottool.h"


class CChartMeasure : public IPlotTool
{
public:
    CChartMeasure(QCustomPlot* plot, int graph_index=0);

    // IPlotTool interface
public:
    EToolType GetType() override;
    void UpdateWithMouseEvent(QMouseEvent *event) override;
    void SetVisibility(bool value) override;
    void SetColor(QColor color) override;
    void SetWorkingGraphIndex(int index) override;
    void SetGeometry(int x, int y, int width, int height) override;
    void UpdateView() override;

private:
    QCPItemText *MeasureCaption = nullptr;
    QCPItemRect *MeasureRect    = nullptr;
    QCPItemLine *MeasureLineHor = nullptr;
    QCPItemLine *MeasureLineVer = nullptr;
    //
    QLabel *MinValueLabel = nullptr;
    QLabel *MinKeyLabel   = nullptr;
    QLabel *MaxValueLabel = nullptr;
    QLabel *MaxKeyLabel   = nullptr;
    //
    QCPRange MeasureValue;
    QCPRange MeasureKey  = QCPRange(0, 0);
    bool Visible         = false;
    bool IsCaptionBottom = false;
    QString Caption      = "";
    QString ValueSuffix  = "";
    QString KeySuffix    = "";
    QFontMetrics *Font;
    QCPItemPixmap *KeyMeasureBegin   = nullptr;
    QCPItemPixmap *KeyMeasureEnd     = nullptr;
    QCPItemPixmap *ValueMeasureBegin = nullptr;
    QCPItemPixmap *ValueMeasureEnd   = nullptr;
    bool UpdateFlag = false;
    QPoint MousePressBegin = QPoint(0, 0);
    QPointF MouseMoveCoord = QPointF(0, 0);
    int KeyPrecision = 1;
    int ValuePrecision = 1;

    enum VerArrowSituation { ATop, ABottom };
    enum HorArrowSituation { ALeft, ARight };

private:
    void SetMaxminCaption(QPointF max, QPointF min);
    void DrawPlotText(QCPItemPixmap *p, QSize boxSize, QString str, QPen textPen, QBrush bckColor, QPointF pos);
    void MouseLeftClickUpdate(QMouseEvent *e);
    void MouseMoveUpdate(QMouseEvent *e);
    void SetValueRange(QCPRange range);
    void SetKeyRange(const QCPRange &key);
    void SetCaption(QString value);
    void SetKeyArrow(HorArrowSituation arrow);
    void setValueArrow(VerArrowSituation arrow);
    void BeginDrawBox(QPoint pos);
    void UpdateDrawBox(QPoint pos);
    void CalculateMaxmin(QCPRange newRange, QPointF &maxx, QPointF &minn);
};

class CChartMeasureBuilder:public IPlotToolBuilder
{
public:
    CChartMeasureBuilder(QCustomPlot *plot);

    // IPlotToolBuilder interface
public:
    void UpdateWithMouseEvent(QMouseEvent *e) override;
    void UpdateView() override;
};

#endif // CHARTMEASURE_H
