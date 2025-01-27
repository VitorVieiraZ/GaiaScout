import QtQuick

Item {
    id: root

    property string iconSource: ""
    property string text: ""
    property bool selected: false
    property bool enabled: true

    signal clicked

    width: 80
    height: parent.height

    Column {
        anchors.centerIn: parent
        spacing: 4

        Image {
            id: icon
            source: root.iconSource
            width: 24
            height: 24
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: enabled ? 1.0 : 0.5
        }

        Text {
            text: root.text
            color: __style.mainColor
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (root.enabled) {
                root.clicked();
            }
        }
    }
}
