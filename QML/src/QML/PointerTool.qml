// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: pointerTool

    property ChartView chartView
    property LineSeries xLineSeries
    property LineSeries yLineSeries

    Component.onCompleted: {
        xLineSeries = chartView.createSeries(ChartView.SeriesTypeLine);
        yLineSeries = chartView.createSeries(ChartView.SeriesTypeLine);
        xLineSeries.style = Qt.DotLine
        yLineSeries.style = Qt.DotLine

        xLineSeries.color = "#443e3e";
        yLineSeries.color = "#443e3e";
        xLineSeries.width = 1.5
        yLineSeries.width = 1.5

    }
    Label{
        id: xvalue
        anchors.right: divider.left
        anchors.verticalCenter: yvalue.verticalCenter
    }

    Label {
        id: divider
        text : " , "
        anchors.right: yvalue.left
        anchors.verticalCenter: yvalue.verticalCenter

    }

    Label{
        id: yvalue

    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPositionChanged: {
            if (mouseX >= 0 && mouseX <= chartView.width) {
                var point = Qt.point(mouseX, mouseY); // Create a point using mouseX as x-coordinate and 0 as y-coordinate
                var visualPosition = chartView.mapToValue(point, chartView.series(0)); // Map the point to a visual position
                if(visualPosition.x<0)
                {
                    xvalue.visible = false

                }
                else
                {
                    xvalue.visible = true
                    xvalue.text = Math.round(visualPosition.x * 100) / 100;

                }
                if(visualPosition.y<0)
                {
                    yvalue.visible = false
                }
                else
                {
                    yvalue.visible = true
                    yvalue.text = Math.round(visualPosition.y * 100) / 100 + " "

                }
                yvalue.x = mouseX - yvalue.width
                yvalue.y = mouseY - yvalue.height
                xLineSeries.clear();
                xLineSeries.append(visualPosition.x, 0);
                xLineSeries.append(visualPosition.x, 100);

                yLineSeries.clear();
                yLineSeries.append(0  ,visualPosition.y);
                yLineSeries.append(100,visualPosition.y);
            }

        }
    }
}
