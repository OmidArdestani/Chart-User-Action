// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts
import QtQuick 2.15


Item {
    id: pointerTool

    property ChartView chartView
    property LineSeries xLineSeries
    property LineSeries yLineSeries

    Component.onCompleted: {
        xLineSeries = chartView.createSeries(ChartView.SeriesTypeLine);
        yLineSeries = chartView.createSeries(ChartView.SeriesTypeLine);

        xLineSeries.color = Qt.black;
        yLineSeries.color = Qt.black;
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPositionChanged: {
            if (mouseX >= 0 && mouseX <= chartView.width) {
                var point = Qt.point(mouseX, mouseY); // Create a point using mouseX as x-coordinate and 0 as y-coordinate
                var visualPosition = chartView.mapToValue(point, chartView.series(0)); // Map the point to a visual position

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
