
#include "actionhandler.h"
#include "Tools/chartmarker.h"
#include <Tools/chartpointer.h>

#include <Tools/chartmeasure.h>
#include <Tools/chartselector.h>

CActionHandler::CActionHandler(QCustomPlot *plot)
    : QObject{plot}
{
    plot->addLayer(PLOT_TOOL_LAYER_NAME);

    PlotTools.insert(EToolType::Marker,new CChartMarkerBuilder(plot));
    PlotTools.insert(EToolType::Pointer,new CChartPointerBuilder(plot));
    PlotTools.insert(EToolType::Measure,new CChartMeasureBuilder(plot));
    PlotTools.insert(EToolType::Selector,new CChartSelectorBuilder(plot));
    // TO DO : insert other tools one by one after implementation
}

void CActionHandler::SetPlotEvent(QMouseEvent *e)
{
    PlotTools.value(ActiveToolType)->UpdateWithMouseEvent(e);
}

void CActionHandler::UpdateView()
{
    PlotTools.value(ActiveToolType)->UpdateView();
}

void CActionHandler::SetActiveTool(EToolType mode)
{
    ActiveToolType = mode;
}


