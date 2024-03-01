// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCharts
import QtQuick 2.15


Item {
    id: markerTool

    property ChartView chartView
    property var scatterSeriesList:[]

    Component.onCompleted: {
        var newSeries = chartView.createSeries(ChartView.SeriesTypeScatter);
        newSeries.color = Qt.black;

        scatterSeriesList.push(newSeries);
    }

    function getSeriesRange(series)
    {
        var min = series.at(0).x, max = series.at(0).x;

        for(var i=0;i<series.count;++i)
        {
            if(series.at(i).x > max)
                max = series.at(i).x;
            if(series.at(i).x < min)
                min = series.at(i).x;
        }
        return [min,max];
    }

    function getYValueForX(series, xValue) {
        var closestPoint;
        let[min,max] = getSeriesRange(series);
        var range = max - min;
        var closestXDistance = range / series.count;

        for (var i = 0; i < series.count; ++i) {
            var point = series.at(i);
            var xDistance = Math.abs(point.x - xValue);

            if (xDistance < closestXDistance)
                closestPoint = point;
        }

        return closestPoint;
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPositionChanged: {
            if (mouseX >= 0 && mouseX <= chartView.width) {
                var point = Qt.point(mouseX, mouseY); // Create a point using mouseX as x-coordinate and 0 as y-coordinate
                var visualPosition = chartView.mapToValue(point, chartView.series(0)); // Map the point to a visual position

                var closestPoint = getYValueForX(chartView.series(0),visualPosition.x);

                scatterSeriesList[scatterSeriesList.length-1].clear();
                scatterSeriesList[scatterSeriesList.length-1].append(closestPoint.x, closestPoint.y);
            }
        }
        onClicked: {
            var newSeries = chartView.createSeries(ChartView.SeriesTypeScatter);
            newSeries.color = Qt.black;

            scatterSeriesList.push(newSeries);
        }
    }
}
