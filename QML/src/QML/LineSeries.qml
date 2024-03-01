// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts
import QtQuick 2.15

ChartView {
    title: "Line Chart"
    id: chartView
    anchors.fill: parent
    antialiasing: true

    LineSeries {
        name: "Line"
        id: mainSeries
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
        XYPoint { x: 4.1; y: 3.3 }
    }

    MarkerTool{
        chartView: chartView
        anchors.fill: parent
        visible: true
    }
    PointerTool{
        chartView: chartView
        anchors.fill: parent
        visible: false
    }
}
