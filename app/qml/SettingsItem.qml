import QtQuick

Rectangle {
  id: settingsItem
  width: parent.width
  height: 48
  color: "transparent"

  signal clicked

  property string text: ""

  Text {
    text: settingsItem.text
    font.pixelSize: 16
    color: __style.mainColor
    anchors {
      left: parent.left
      verticalCenter: parent.verticalCenter
    }
  }

  Image {
    source: __style.nextIcon
    width: 24
    height: 24
    anchors {
      right: parent.right
      verticalCenter: parent.verticalCenter
    }
  }

  MouseArea {
    anchors.fill: parent
    onClicked: settingsItem.clicked()
  }
}
