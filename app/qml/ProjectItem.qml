import QtQuick

Rectangle {
  id: root
  width: parent.width
  height: 120
  radius: 12
  color: __style.secondaryColor

  border {
    width: 2
    color: __style.mainColor
  }

  property string title: ""
  property string lastModified: ""
  property string description: ""
  property string projectId: ""

  signal clicked
  signal deleteClicked

  Row {
    anchors {
      left: parent.left
      right: parent.right
      top: parent.top
      margins: 12
    }
    spacing: 8

    Column {
      width: parent.width - parent.spacing
      spacing: 8

      Text {
        text: root.title
        font.pixelSize: 18
        font.bold: true
        color: __style.mainColor
      }

      Text {
        text: root.description
        font.pixelSize: 14
        color: __style.mainColor
        wrapMode: Text.WordWrap
        width: parent.width
      }

      Text {
        text: "Created: " + root.lastModified
        font.pixelSize: 14
        color: __style.mainColor
      }
    }
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {
      root.clicked()
    }
  }
}
