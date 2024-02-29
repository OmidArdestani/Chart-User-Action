// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Rectangle {
    id: root
    width: 1200
    height: 600

    color: "#f0f0f0"

    property bool isHorizontalView: root.width >= root.height

    Item {
        anchors.fill: parent
        anchors.margins: 8

        Rectangle {
            width: isHorizontalView ? parent.width : parent.width
            height: isHorizontalView ? parent.height : parent.height
            radius: 5
            x: 0
            y: 0
            clip: true

            Loader {
                anchors.fill: parent
                asynchronous: true
                source: "LineSeries.qml"
            }
        }
    }
}
