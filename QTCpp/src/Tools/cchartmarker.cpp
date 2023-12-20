
#include "cchartmarker.h"

CCahrtMarker::CCahrtMarker(QObject *parent)
    : QObject{parent}
{

}


ToolType Marker::GetType()
{
    return ToolType::Marker;
}

void Marker::Update(QMouseEvent *event)
{

}

void Marker::ShowSetting()
{

}

void Marker::SetVisibility()
{

}
