import QtQuick

Item {
    id: root
    anchors.centerIn: parent
    width: 20
    height: 20
    visible: false

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: 2
        color: "black"
    }

    Rectangle {
        anchors.centerIn: parent
        width: 2
        height: parent.height
        color: "black"
    }
}
